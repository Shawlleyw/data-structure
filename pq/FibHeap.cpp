/*
two sides
*/
#include<bits/stdc++.h>
using namespace std;

template <class T>
class FibonacciHeap{
    typedef struct FibonacciNode{
        int degree , value ;
        FibonacciNode * left ;
        FibonacciNode * right ;
        FibonacciNode * son ;

        /*FibonacciNode() {      //     ----------invalid in malloc  ----------------------  why?
            degree = 0;
            value = 0;
            left = NULL;
            right = NULL;
            son = NULL;
        }*/

        void init () {            
            degree = 0;
            value = 0;
            left = NULL;
            right = NULL;
            son = NULL;
        }

    }fibnode;
    
    int count, maxdegree;
    fibnode * minnode;
    fibnode ** buffer;

    void insert (fibnode * node, fibnode * root){     //inster a node into the list
        if(root -> right != NULL) root -> right -> left = node;
        node -> right =  root -> right;
        node -> left = root;
        root -> right = node;
    }

    void remove(fibnode * node) {     // remove a node from the list
        if(node -> left != NULL) node -> left -> right = node -> right;  // == node ? node -> left -> right : node -> right;   
        if(node -> right != NULL) node -> right -> left = node -> left;   // == node ? node -> right -> left : node -> left;
    }

    void exchange(fibnode *x, fibnode *y){
        fibnode current = *y;
        y -> left = x -> left ;
        y -> right = x -> right;
        x -> left = current.left;
        x -> right = current.right;
        if( x -> left == x) x -> left = y;
        if( y -> right == y) y -> right = x;
        
    }

    fibnode * extract() {
        fibnode * node = minnode;
        if(minnode -> right == NULL && minnode -> left == NULL) minnode = NULL;
        else {
            remove(node);
            minnode = minnode -> right;
        } 
        node -> left = NULL;
        node -> right = NULL;
        return node;
    }

    void memoryrealloc() {
        int preview = maxdegree;
        maxdegree = log2(count) + 1;
        if(preview >= maxdegree) return ;
        buffer = (fibnode **)realloc (buffer, sizeof(fibnode)*(maxdegree +1));
    }

    void link(fibnode * root, fibnode * son){
        remove(son);
        if(root -> son == NULL) root -> son = son;
        else insert (son, root -> son);
    }

    void mergetree(){
        memoryrealloc();
        for(int i = 0; i <= maxdegree + 1; i++)
            buffer[i] = NULL;
        fibnode * nodex, * nodey;
        while(minnode != NULL){
            nodex = extract();
            while( (nodey = buffer[nodex -> degree])!= NULL){
                if( nodex -> value > nodey -> value) swap(nodex, nodey);
                link(nodex, nodey); 
                buffer[nodex -> degree]=NULL; 
                nodex -> degree ++;
            }
            buffer[nodex -> degree] = nodex;
            //printf("merge_error ");
        }
        minnode = NULL;
        for(int i = 0; i <= maxdegree + 1; i++){
            if(buffer[i] == NULL)continue;
            if(minnode == NULL)minnode = buffer[i];
            else{
                insert (buffer[i], minnode);
                if(buffer[i] -> value < minnode -> value){
                	exchange(minnode,buffer[i]);
                	minnode = buffer[i];
				}
            }
        }
    }


    public:

    FibonacciHeap () {
        count = 0;
        maxdegree = 0;
        minnode = NULL;
        buffer = NULL;
    }

    void init(){   // initialize the Heap
        count = 0;
        maxdegree = 0;
        minnode = NULL;
        buffer = NULL;
    }
    
    bool empty () const{    //  return if the queue is empty
        return count == 0;
    }

    string::size_type size() const{   // return the number of elements
        return count;
    }

    const int top () const{   // return the value of the head
        return minnode -> value;
    }

    void push(const T &x) {   // push a new element into the tail of the queue
        fibnode * node = (fibnode * ) malloc (sizeof(fibnode)); 
        //if(node == NULL)return 0;
        node -> init(); node -> value = x;
        //printf("%d %d %d",node -> value, node , node -> son);  //--------check initialize
        if (minnode == NULL) minnode = node;
        else {
            insert (node, minnode);
            if(x < minnode -> value){
            	exchange(minnode, node);
            	minnode = node;
			}
        }
        count++;
        //return 1;
    }

    void pop(){
        //if(empty())return 0;
        while( minnode -> son != NULL){
            remove(minnode -> son);
            fibnode * temp = minnode -> son -> right;
            insert (minnode -> son, minnode);
            minnode -> son = temp;
        }
        remove(minnode);
        fibnode *current = minnode;
        if(minnode -> right == NULL){
        	free(minnode);
			minnode = NULL;
		}
        else {
            minnode = minnode -> right;
            free(current);
            mergetree();
        } 
        count--;
        //return 1;
    }
};

FibonacciHeap<int> H;
void test (){  //----------------used to test the function of the Fibo _Heap
    int c,x,T;
    scanf("%d",&T);   
    while(T--){
        scanf("%d",&c);
        //printf("%d : ",c);
        switch (c){
            case 1 : scanf("%d",&x); H.push (x);break;
            case 2 : H.pop();break;
            case 3 : printf("%d",H.top());break;
            case 4 : printf("%d",H.size());break;
            case 5 : printf(H.empty()?"YES":"NO");break;
        }
        puts("");
    }
}

int main(){
    /*fibheap * heap = (fibheap * ) malloc (sizeof(fibheap));
    heap -> init();
    test (heap);
    free(heap);
    */
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    test();
    return 0;
}
