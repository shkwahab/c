#include <stdio.h> 
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

class text_t_node
{
        public:
                int no_lines;
                text_t_node   *left;
                text_t_node  *right;
                int height;
                
};

class text_t
{
    public:
            text_t_node* root;
};
 

int max(int a, int b)
{
  return (a>b)? a:b;
}

int height(text_t_node *node)
{
  if(node==NULL)
    return 0;
  return node->height;
}

#define BLOCKSIZE 256

text_t_node *currentblock = NULL;
int    size_left;
text_t_node *free_list = NULL;
int nodes_taken = 0;
int nodes_returned = 0;

text_t_node *get_node()
{ text_t_node *tmp;
  nodes_taken += 1;
  if( free_list != NULL )
  {  tmp = free_list;
     free_list = free_list -> right;
  }
  else
  {  if( currentblock == NULL || size_left == 0)
     {  currentblock =
                (text_t_node *) malloc( BLOCKSIZE * sizeof(text_t_node) );
        size_left = BLOCKSIZE;
     }
     tmp = currentblock++;
     size_left -= 1;
  }
  return( tmp );
}

void return_node(text_t_node *node)
{  node->right = free_list;
   free_list = node;
   nodes_returned +=1;
}

text_t_node* rightrotate(text_t_node *x)
{
  text_t_node *tmp_node = x->left;
  text_t_node *other_node = tmp_node->right;

  x->left = other_node;
  tmp_node->right = x;

  x->height = max(height(x->left), height(x->right))+1;
  tmp_node->height = max(height(tmp_node->left), height(tmp_node->right))+1;

  x->no_lines = x->left->no_lines + x->right->no_lines;
  tmp_node->no_lines = tmp_node->left->no_lines + tmp_node->right->no_lines;
  
  return tmp_node;

}

text_t_node* leftrotate(text_t_node *x)
{
  text_t_node *tmp_node = x->right;
  text_t_node *other_node = tmp_node->left;

  
  x->right = other_node;
  tmp_node->left = x;

  x->height = max(height(x->left), height(x->right))+1;
  tmp_node->height = max(height(tmp_node->left), height(tmp_node->right))+1;

  x->no_lines = x->left->no_lines + x->right->no_lines;
  tmp_node->no_lines = tmp_node->left->no_lines + tmp_node->right->no_lines;
  
  return tmp_node;
}

int getBalance(text_t_node *x) 
{ 
    if (x == NULL) 
        return 0; 
    return height(x->left) - height(x->right); 
}

text_t *create_text(void)
{
   text_t_node *tmp_node;
   
   tmp_node = get_node();
   tmp_node->left = NULL;
   tmp_node->no_lines = 0;
   tmp_node->height = 1;
   
   text_t *tmp_tree = (text_t *) malloc( BLOCKSIZE * sizeof(text_t) );
   tmp_tree->root = tmp_node;
   
   return( tmp_tree );
}


int length_text(text_t *text)
{
   if(text == NULL || text->root == NULL)
        return -1;
   return(text->root->no_lines);
}

char* get_line(text_t *text, int index)
{
   text_t_node *txt = text->root; 
   text_t_node *tmp_node = txt;
   
   if( txt->left == NULL )
      return (NULL);
   else if(index<1 || index>tmp_node->no_lines)
      return(NULL);
   else
   {
      tmp_node = txt;
      while(tmp_node->right != NULL)
      {
          if(index <= tmp_node->left->no_lines)
                tmp_node = tmp_node->left;
          else
          {
                index -= tmp_node->left->no_lines;
                tmp_node = tmp_node->right;
          }

      }

      if(tmp_node->no_lines == 1)
         return ((char *) tmp_node->left);
      else
         return (NULL);
   }

}


char* set_line(text_t *text, int index, char * new_line)
{
   text_t_node *txt = text->root; 
   text_t_node *tmp_node = txt;
   
   if( txt->left == NULL )
      return (NULL);
   else if(index<1 || index>tmp_node->no_lines)
      return(NULL);
   else
   {
      tmp_node = txt;
      while(tmp_node->right != NULL)
      {
          if(index <= tmp_node->left->no_lines)
                tmp_node = tmp_node->left;
          else
          {
                index -= tmp_node->left->no_lines;
                tmp_node = tmp_node->right;
          }

      }
      
      char *line_removed;
      
      if(tmp_node->no_lines == 1)
      {
          line_removed = (char *) tmp_node->left;
          tmp_node->left = (text_t_node *) new_line;
         return line_removed;
      }
      else
         return (NULL);
   }

}


void insert_line(text_t *text, int index, char* new_line)
{
    text_t_node *txt = text->root;
   text_t_node *tmp_node;
   int side = 0;

   if( txt->left == NULL )
   {  txt->left = (text_t_node *) new_line;
      txt->no_lines  = 1;
      txt->height = 1;
      txt->right  = NULL;
   }
   else
   {
      tmp_node = txt;
      int nline_no = index;
      vector <text_t_node*> vec;
      vector <int> lrside;
      while( tmp_node->right != NULL )
      {
      	vec.push_back(tmp_node);
      	tmp_node->no_lines +=1;
      	if(nline_no<=tmp_node->left->no_lines)
      	{
      		tmp_node = tmp_node->left;
      		side = 0;
      		lrside.push_back(side);
      	}
		else
          {
                nline_no -= tmp_node->left->no_lines;
                tmp_node = tmp_node->right;
                side = 1;
                lrside.push_back(side);
          }
      }

      text_t_node *old_leaf, *new_leaf;
      old_leaf = get_node();
      old_leaf->left = tmp_node->left;
      old_leaf->no_lines = tmp_node->no_lines;
      old_leaf->height = tmp_node->height;
      old_leaf->right  = NULL;

      new_leaf = get_node();
      new_leaf->left = (text_t_node *) new_line;
      new_leaf->no_lines = 1;
      new_leaf->height = 1;
      new_leaf->right  = NULL;

      if( tmp_node->no_lines < nline_no )
      {   tmp_node->left  = old_leaf;
          tmp_node->right = new_leaf;
          tmp_node->no_lines +=1;
          tmp_node->height +=1;
      }
      else
      {   tmp_node->left  = new_leaf;
          tmp_node->right = old_leaf;
          tmp_node->no_lines +=1;
          tmp_node->height +=1;
      }

      if(vec.size()>0)
      {
        text_t_node* tmp;
        for(int i = vec.size()-1;i>=0;i--)
        {
            int isroot = 0;
            tmp = vec[i];
          	tmp->height = max(height(tmp->left), height(tmp->right))+1;
      	    int balance = getBalance(tmp);
          	nline_no+=tmp->left->no_lines;
          	
          	if(text->root == tmp)
          	    isroot = 1;
          	
          	if(balance < -1 && side == 1)
        	{
      	    	tmp = leftrotate(tmp);
      	    	
      	    	if(!isroot)
      	    	{
      	    	    if(lrside[i-1] == 1)
      	    	        vec[i-1]->right = tmp; 
      	    	    else
      	    	        vec[i-1]->left = tmp;
      	            
      	        }
      	    }

      	    else if(balance < -1 && side == 0)
      	    {
          		tmp->right = rightrotate(tmp->right); 
            	tmp = leftrotate(tmp); 
            	
            	if(!isroot)
      	    	{
      	    	    if(lrside[i-1] == 1)
      	    	        vec[i-1]->right = tmp; 
      	    	    else
      	    	        vec[i-1]->left = tmp;
      	            
      	        }
      	    }

      	    else if(balance > 1 && side == 0)
      	    {
          		tmp = rightrotate(tmp);
          		
          		if(!isroot)
      	    	{
      	    	    if(lrside[i-1] == 1)
      	    	        vec[i-1]->right = tmp; 
      	    	    else
      	    	        vec[i-1]->left = tmp;
      	            
      	        }
      	    }
      	    else if(balance > 1 && side == 1)
      	    {
          		tmp->left = leftrotate(tmp->left);
      		    tmp = rightrotate(tmp);
      		    
      		    if(!isroot)
      	    	{
      	    	    if(lrside[i-1] == 1)
      	    	        vec[i-1]->right = tmp; 
      	    	    else
      	    	        vec[i-1]->left = tmp;
      	            
      	        }
      	    }
      	    
      	    if(isroot == 1)
      	        text->root = tmp;
         }
        txt = tmp;
      }
   }
}

void append_line( text_t *text, char * new_line)
{
   text_t_node *txt = text->root;
   text_t_node *tmp_node;
   int side = 0;
   
   if( txt->left == NULL )
   {  txt->left = (text_t_node *) new_line;
      txt->no_lines  = 1;
      txt->height = 1;
      txt->right  = NULL;
   }

   else
   {
      int last_ind = length_text(text)+1;
      insert_line(text, last_ind, new_line);
    
   }
}


char* delete_line(text_t *text, int index)
{  
    text_t_node* txt = text->root;
    text_t_node *tmp_node, *upper_node, *other_node;
   char* deleted_object;
   if( txt->left == NULL )
      return( NULL );
   else if( txt->right == NULL )
   {
      
      if(  txt->no_lines == index )
      {  deleted_object = (char *) txt->left;
         txt->no_lines-=1;
         txt->height-=1;
         txt->left = NULL;
         return( deleted_object );
      }
      else
         return( NULL );
   }
   else
   {  tmp_node = txt;
      vector <text_t_node*> vec;
      vector <int> lrside;
      
      while( tmp_node->right != NULL )
      {
          tmp_node->no_lines-=1;
          upper_node = tmp_node;
          vec.push_back(upper_node);

          if( index <= tmp_node->left->no_lines )
          {
             tmp_node   = upper_node->left;
             other_node = upper_node->right;
             lrside.push_back(0);
          }
          else
          {
             index-=tmp_node->left->no_lines;
             tmp_node   = upper_node->right;
             other_node = upper_node->left;
             lrside.push_back(1);
          }
      }
      if( tmp_node->no_lines != 1 )
         return( NULL );
      else
      {
         upper_node->left  = other_node->left;
         upper_node->right = other_node->right;
         upper_node->height -= 1;
         deleted_object = (char *) tmp_node->left;
         return_node( tmp_node );
         return_node( other_node );
         
         if(vec.size()>0)
         {
            text_t_node* tmp;
            for(int i = vec.size()-2; i>=0; i--)
            {
                int isroot = 0;
                tmp = vec[i];
            
                int balance = getBalance(tmp);
                if(text->root == tmp)
                    isroot = 1;
                    
                if(balance < -1 && getBalance(tmp->right) == 0)
                {
                    tmp = leftrotate(tmp);
              
                    if(!isroot)
                    {
                      if(lrside[i-1] == 1)
                          vec[i-1]->right = tmp; 
                      else
                        vec[i-1]->left = tmp;
                    
                    }
                }

                else if(balance < -1 && getBalance(tmp->right) == 1)
                {
                    tmp->right = rightrotate(tmp->right); 
                    tmp = leftrotate(tmp); 
              
                    if(!isroot)
                    {
                        if(lrside[i-1] == 1)
                        vec[i-1]->right = tmp; 
                    else
                        vec[i-1]->left = tmp;
                    
                    }
                }

                else if(balance > 1 && getBalance(tmp->left) == 0)
                {
                    tmp = rightrotate(tmp);
              
                    if(!isroot)
                    {
                        if(lrside[i-1] == 1)
                            vec[i-1]->right = tmp; 
                        else
                            vec[i-1]->left = tmp;
                    
                    }
                }
                else if(balance > 1 && getBalance(tmp->left) == 0)
                {
                    tmp->left = leftrotate(tmp->left);
                    tmp = rightrotate(tmp);
              
                    if(!isroot)
                    { 
                        if(lrside[i-1] == 1)
                            vec[i-1]->right = tmp; 
                        else
                            vec[i-1]->left = tmp;
                    }
                }
            
                if(isroot == 1)
                    text->root = tmp;
            }
           
            txt = tmp; 
         }
         return( deleted_object );
      }
   }
}


int main()
{
    int i, tmp; 
    text_t *txt2; 
    char *c;


    txt2 = create_text();
//     for(i=1; i<=10000; i++){  
//         if( i%2==1 )
//             append_line(txt2, "A");
//         else 
//             append_line(txt2, "B");
//     }

//     cout<<length_text(txt2)<<endl;
    
//     cout<<get_line(txt2, 9876 )<<endl;

//     for( i= 10000; i > 1; i-=2 ){  
//         c = delete_line(txt2, i);
//         if(!(*c == 'B'))
//             cout<<"line "<<i<< "of txt2 should be B, found "<<c<<endl;
//         append_line( txt2, c );
//    }
//     for( i=1; i<= 5000; i++ ){
//         c = get_line(txt2, i);
//         if(!(*c == 'A'))
//             cout<<"line "<<i<< "of txt2 should be A, found "<<c<<endl;
//     }


//     for( i=1; i<= 5000; i++ ){
//         delete_line(txt2, 1 );
//     }

//     for( i=1; i<= 5000; i++ ){
//         c = get_line(txt2, i);
//         if(!(*c == 'B'))
//             cout<<"line "<<i<< "of txt2 should be B, found "<<c<<endl;
//     }

//     for( i=99; i>=1; i-- ){
//         delete_line(txt2, i );
//     }
    // set_line(txt2, 1, "the first line");
    // set_line(txt2, 2, "the second line");clea
    insert_line(txt2,1,"a b c");
    insert_line(txt2,2,"d e f");
    cout<<get_line(txt2, 1)<<endl;
    cout<<get_line(txt2, 2)<<endl;
    cout<<length_text(txt2)<<endl;
   return 0;
}
