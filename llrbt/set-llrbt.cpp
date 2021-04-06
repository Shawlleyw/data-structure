#include<bits/stdc++.h>
using namespace std;

template <class E> 
class Set{
    
    private:

    static const bool RED = true;
    static const bool BLACK = false;

    struct Node{
        E value;
        int size;
        bool color;
        Node * left;
        Node * right;
        Node * pre;
        Node * suf;

        void initialize(E key, Node * prev, Node * suff){
            left = NULL;
            right = NULL;
            pre = prev;
            suf = suff;
            value = key;
            color = RED;  
            size = 1;
        }

    };

    Node * root;
    int total_size;

    void initialize(){
        root =NULL;
        total_size = 0;
    }

    void release(Node * node){
        if(node == NULL)return;
        release (node -> left);
        release (node -> right);
        delete node; 
		node =NULL;
    }

    /*
	void pushup(Node * node){
        int count = 1;
        if(node -> left !=NULL) count += node -> left -> size;
        if(node -> right !=NULL) count += node -> right -> size;
        node -> size = count;
    }
	*/

    Node * rotate(Node * node, bool isright){ 
        Node * temporary = isright ? node -> right : node -> left;
        if(isright){
            node -> right = temporary -> left;
            temporary -> left = node;
        }
        else{
            node -> left = temporary -> right;
            temporary -> right = node;
        }
        temporary -> color = node -> color; 
        node -> color = RED;
        //pushup(node);
        //pushup(temporary);
        return temporary;
    }

    void flip(Node * node){
        node -> color = !node -> color;
        if(node -> left !=NULL) node -> left -> color = !node -> left -> color;
        if(node -> right !=NULL) node -> right -> color = !node -> right -> color;
    }

    Node * balance(Node * node){
        bool leftred = node -> left !=NULL && node -> left -> color == RED;
        bool rightred =  node -> right !=NULL && node -> right -> color == RED;
        bool leftleftred = node -> left !=NULL && node -> left -> left !=NULL && node -> left -> left -> color == RED;
        if(!leftred && rightred) node = rotate(node, true);         //true for rightson
        if(leftred && leftleftred) node = rotate(node, false);      //false for leftson
        if(leftred && rightred) flip(node);      
        return node;
    }

    Node * add(Node * current, E key, Node * prev, Node * suff){
        if(current ==NULL){
            Node * node = new Node;
            node -> initialize(key, prev, suff); 
            if(prev !=NULL && (prev -> suf ==NULL || prev -> suf -> value > key)) prev -> suf = node;
            if(suff !=NULL && (suff -> pre ==NULL || suff -> pre -> value < key)) suff -> pre = node;
            return node;
        }
        if(key == current -> value ) return balance(current);
        if(current -> value > key) current -> left = add(current -> left, key, prev, current);
        else current -> right = add(current -> right, key, current, suff);
        return balance(current);
    }

    Node * reddownleft(Node * node){
        flip(node);
        bool rightleftred = node -> right !=NULL && node -> right -> left !=NULL && node -> right -> left -> color == RED;
        if(rightleftred){
            node -> right = rotate(node -> right, false);
            node = rotate(node, true);
            flip(node);
        }
        return node;
    }

    Node * reddownright(Node * node){
        flip(node);
        bool leftleftred = node -> left !=NULL && node -> left -> left !=NULL && node -> left -> left -> color == RED;
        if(leftleftred){
            node = rotate(node, false);
            flip(node);
        }
        return node;
    }

    Node * delmin(Node * node){
        if(node -> left == NULL){
            Node * temp = node -> right;
			delete node; node = NULL;
            return temp;
        }
        bool leftred = node -> left !=NULL && node -> left -> color == RED;
        bool leftleftred = node -> left !=NULL && node -> left -> left !=NULL && node -> left -> left -> color == RED;
        if(!leftred && !leftleftred) node = reddownleft(node);
        node -> left = delmin(node -> left);
        return balance(node);
    }

    Node * getmin(Node * node){
        while(node -> left !=NULL) node = node -> left;
        return node;
    }

    Node * del(Node * node, const E & key){
    	if(node == NULL) return NULL;
        bool leftred = node -> left !=NULL && node -> left -> color == RED;
        bool leftleftred = node -> left !=NULL && node -> left -> left !=NULL && node -> left -> left -> color == RED;
        if(key < node -> value){
            if(!leftred && !leftleftred) node = reddownleft(node); 
            node -> left = del(node -> left, key);
        }
        else{
            if(leftred) node = rotate(node, false);
            if(node -> value == key && node -> right ==NULL){
            	if( node -> suf != NULL) node -> suf -> pre = node -> pre;
            	if( node -> pre != NULL) node -> pre -> suf = node -> suf;
            	Node * temp = node -> left;
            	delete node;
            	return temp;
			}
            bool rightred = node -> right !=NULL && node -> right -> color == RED;
            bool rightleftred = node -> right !=NULL && node -> right -> left !=NULL && node -> right -> left -> color == RED;
            if(!rightred && !rightleftred) node = reddownright(node);
            if(key == node -> value){
                node -> size --;
                Node * temp = getmin(node -> right);
				node -> value = temp -> value;
				node -> suf = temp -> suf;
				if(temp -> suf !=NULL) temp -> suf -> pre = node;
                node -> right = delmin(node -> right);
                //pushup(node);
                return node;
            }
            else node -> right = del(node -> right, key);
        }
        return balance(node);
    }

    bool exist(Node * node, E key){
        if(node ==NULL)return 0;
        if(node -> value == key) return 1;
        return exist(node -> value > key ? node -> left : node -> right, key);
    }

    Node * locate(Node * node, E key){
        if(node ==NULL) return NULL;
        if(node -> value == key) return node;
        return locate(node -> value > key ? node -> left : node -> right, key); 
    }

    Node * pre(Node * node, E key){
        if(node ==NULL) return NULL;
        if(node -> value > key) return pre(node -> left, key);
        Node * flag;
        flag = pre(node -> right, key);
        return flag ==NULL ? node : flag;
    }

    Node * suf(Node * node, E key){
        if(node ==NULL) return NULL;
        if(node -> value < key) return suf(node -> right, key);
        Node * flag;
        flag = suf(node -> left, key);
        return flag ==NULL ? node : flag;
    }

    public:
	
    Set(){
        root =NULL;
        total_size = 0;
    }

	~ Set(){
		clear();
	}
	
    bool empty() const {
        return total_size == 0;
    }

    string::size_type size() const {
        return total_size;
    }

    void clear(){
        release(root);
        initialize();
    }

    void insert(const E& key){  // bu neng di tui && zhi neng di gui
    	if(count(key)) return ;
        root = add(root, key,NULL,NULL);
        total_size ++;
        root -> color = BLACK;
		//printf("%d\n", root -> value);
        /*       di tui 
        if(root ==NULL) {
            root = node ;
            root -> color = BLACK;
            return ;
        }
        bool isright = false;
        Node * current = root, * father;
        while(current !=NULL){
            current -> size ++;
            father = current;
            if(current.value == key) return ;
            if(current.value > key){
                current = current -> left;
                isright =  false;
            }
            else{
                current = current -> right;
                isright = true;
            }
        }
        if(isright) father -> right = node;
        else father -> left = node;
        */

    }
    
    void erase(const E& key){
        if(!count(key))return;
        root = del(root, key);
        total_size --;
        if(total_size > 0) root -> color = BLACK;
    }

    int count(const E& key){
        return exist(root, key) ? 1 : 0;
    }

    class Iterator{
        
        Node * node;

        public:

        Iterator (){
            node =NULL;
        }
		Iterator (Node * temp){
            node = temp;
        }
        
        Iterator operator++(int) {
            /*
            Iterator temporary;
            if(node ==NULL) temporary.node = begin(); 
            temporary.node = lower_bound(node -> value + 1);
            return temporary;
            */
            Iterator temp = *this;
            node = node -> suf;
            return temp; 
        }
		

        Iterator &operator++() {
            /*
            Iterator temporary;
            if(node ==NULL) temporary.node = begin(); 
            temporary.node = lower_bound(node -> value + 1);
            return temporary;
            */
            node = node -> suf;
            return *this; 
        }

        Iterator &operator--() {
            /*
            Iterator temporary;
            if(node ==NULL) temporary.node = end(); 
            else temporary.node = upper_bound(node -> value - 1);
            return temporary;
            */
            node = node -> prev;
            return *this;
        }

        Iterator operator--(int) {
            /*
            Iterator temporary;
            if(node ==NULL) temporary.node = end(); 
            else temporary.node = upper_bound(node -> value - 1);
            return temporary;
            */
            Iterator temp = *this;
            node = node -> prev;
            return temp;
        }

        bool operator ==(const Iterator &x) const{
            return node == x.node;
        }

        bool operator !=(const Iterator &x) const {
           return node != x.node;
        }

        E operator*() const{
            return node -> value;
        }
        
    };
	
	Iterator begin(){
        Node * node = root;
        while(node -> left !=NULL)node = node -> left;
        return Iterator(node);
    }

    Iterator end(){
        Node * node = root;
        while(node -> right !=NULL)node = node -> right;
        return Iterator(node);
    }

    Iterator  lower_bound(const E& key){
        Iterator temporary;
        temporary -> node = suf(root, key);
        return temporary;
    }

    Iterator  upper_bound(const E& key){
        Iterator temporary;
        temporary -> node = pre(root, key);
        return temporary;
    }

    Iterator find(const E& key){
        Iterator temporary;
        temporary -> node = locate(root, key);
        return temporary;
    }
 //------------------------------debug--------------------------  
    private: void printtree(Node * node, int fa, int fg){
    	if(node ==NULL)return;
    	if(!fg)printf("%d left:%d\n", fa, node -> value);
    	else printf("%d right:%d\n", fa, node -> value);
    	printtree(node -> left, node -> value, 0);
    	printtree(node -> right, node -> value, 1);
	}
	public: void printtree(){
		printtree(root, 0, 0);
	}
	private: void checkstate(Node * node){
		if(node == NULL) return;
		int x = 0,p = 0,s = 0,fg = 0;
		x = node -> value;
		if(node -> pre !=NULL){
			p = node -> pre -> value;
			if( p != x - 2) fg = 1;
		}
		if(node -> suf !=NULL){
			s = node -> suf -> value;
			if(s != x + 2)fg = 1;
		}
		if(fg){
			puts("NIE");
			printf("%d %d %d",p,x,s);
			getchar();
		}
		checkstate(node -> left);
		checkstate(node -> right);
	}
	public: void state(){
		checkstate(root);
	}
};
Set<int> S;
Set<int>::Iterator IT;
set<int> s;
set<int>::iterator it;
int n = 100;
void Insert(){
	for(int i = 1; i <= n; i++)
	S.insert(i);
	S.printtree();
}
void Check(){
	S.state();
}
void Erase(){
	for(int i = 1; i <= n; i++)
	S.erase(i);
}
void Checkit(){
	IT = S.begin();
	it = s.begin();
	int x;
	while(IT != S.end()){
		if(*it != *IT){
			puts("FUCK");
			printf("%d %d\n",*IT, *it);
			scanf("%d",&x);
		}
		it++;IT++;
	}
	//puts("");
}
void randomtest(){
    srand(time(0));
    int *ptr = (int * )malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
		ptr[i] = rand() +1;
    	//printf("%d ", );
	}
	puts("");
    int x;
    for(int i=0;i<n;i++){
        //x = (abs(rand()))%n ;
        x = ptr[i];
        S.insert(x);
        s.insert(x);
        //Checkit();
    }
    for(int i=0;i<n;i++){
      x = ptr[i];
      S.erase(x);
      s.erase(x);
      //printf("Erase: %d \n",x);
      if(i == n-1)continue;
      Checkit();
	  
    }
    free(ptr);
}
int main(){
    randomtest();
    //Insert();
    //Checkit();
    //Erase();
    //Check();
    return 0;
}
