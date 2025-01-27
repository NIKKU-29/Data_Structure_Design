#include <iostream>
#include <unordered_map>
using namespace std; 

//The Node represents the single node of a doubly linked list.
class Node{
    public:
    int key;
    int value;
    Node* next;
    Node* prev;
    Node(int k, int v){
        key = k;
        value = v;
        next = NULL;
        prev = NULL;
    }
};

//=========================================================================
//Below we have created a hash table that contains key -> {data,Node} 
//We have also created a head pointer pointing to the front and the tail
//pointer points to the end. 
//We have created these pointers so that we don’t have to 
//traverse the complete linked list.


class LRUCache {

    unordered_map<int,pair<int,Node*>>mp;
    Node* head;
    Node* tail;
    int cap;

public:
    LRUCache(int capacity) {
        cap = capacity;
        head = new Node(-1,-1);
        tail = new Node(-1,-1);
        head->next = tail;
        tail->prev = head;
    }

//=========================================================================
//The get() method will take the key of data 
//and returns the data corresponding to that key. 
//Here if the key is present then we will remove it 
//from that place and insert it at the front of the list and 
//now it will become most frequently used data.

    int get(int key)
    {
        //if not found in map then return -1
        if(mp.find(key)==mp.end())
        {
            return -1;
        }

        //if find then remove from the list and insert at the front;
        else
        {
            int ans=mp[key].first;
            Node*temp=mp[key].second;
            remove(temp);
            mp[key].second=insert(ans,key);
            return ans;
        }
    }


//=========================================================================
//The put() method will take the key and corresponding value 
//and insert it into the hashmap and list.
//If the key is present we remove it from the list 
//and then insert it at the front because it's used recently.
//If cache size is full we remove least frequently used element.


    void put(int key,int value)
    {
        if(mp.find(key)==mp.end()) //not found in map need to be inserted
        {
            if(mp.size() < cap) //check size if no space left remove LFU
            {
                mp[key]={value,insert(value,key)};
            }

            else{

                int k=tail->prev->key;
                remove(tail->prev);
                mp.erase(k);
                mp[key]={value,insert(value,key)};

            }
        }

        else{
                 Node*temp=mp[key].second; 
                 remove(temp);
                 mp[key]={value,insert(value,key)};         
        }
    }



//=========================================================================
//This is insertion in DLL hwo it works
//we create a new node with key and values
//we insert them after head and before head->next 
//then normally join DLL both ways.

    Node* insert(int val,int key)
    {
        Node* To_add=new Node(key,val);
        Node*temp=head->next;
        head->next=To_add;
        To_add->prev=head;
        To_add->next=temp;
        temp->prev=To_add;
        return To_add;
    }
//=========================================================================
//This is removal in DLL how it works
//we have temp node and we get its prev and next
//we connect prev->next to next and next->prev to prev
//this way temp node gets unlinked from DLL

    void remove(Node* temp)
    {
        Node*prev=temp->prev;
        Node*next=temp->next;
        prev->next=next;
        next->prev=prev;
    }

};

//driver code
int main() {
    LRUCache lru(2);  // Create cache with capacity 2
    
    // Test put operations
    lru.put(1, 1);
    lru.put(2, 2);
    
    // Test get operations
    cout << lru.get(1) << endl;    // returns 1
    
    // Test eviction
    lru.put(3, 3);                 // evicts key 2
    cout << lru.get(2) << endl;    // returns -1 (not found)
    
    // Test updating existing key
    lru.put(4, 4);                 // evicts key 1
    cout << lru.get(1) << endl;    // returns -1 (not found)
    cout << lru.get(3) << endl;    // returns 3
    cout << lru.get(4) << endl;    // returns 4
    
    return 0;
}