/*
 Chris Jackson
 CSE 232 Section 10
 Project 11
 */
#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream; using std::cout; using std::endl;
#include<string>
using std::string;
#include<utility>
using std::pair; using std::swap;
#include<initializer_list>
using std::initializer_list;
#include<sstream>
using std::ostringstream;


//
// Node
//
template<typename K, typename V>
struct Node {
    K first;
    V second;
    Node *next = nullptr;
    
    Node() = default;
    Node(K,V);
    bool operator<(const Node&) const;
    bool operator==(const Node&) const;
    friend ostream& operator<<(ostream &out, const Node &n){//prints node out in format "first:second"
        out << n.first << ":" << n.second;
        return out;
    }
};

/*.first and .second constructor*/
template<typename K, typename V>
Node<K,V>::Node(K key, V value){
    first = key;
    second = value;
}

/*Checks if one node is less than the other. Returns true if it is, false if it isn't.*/
template<typename K, typename V>
bool Node<K,V>::operator<(const Node &n) const{
    //cout<<"=== operator< ==="<<endl;
    return first<n.first;
}

/*Checks if two nodes are equal. Returns true if they are, false if they aren't.*/
template<typename K, typename V>
bool Node<K,V>::operator==(const Node &n) const{
    return first==n.first;
}






//
// MapSet
//
template<typename K, typename V>
class MapSet{
private:
    Node<K,V>* head_ = nullptr;
    Node<K,V>* tail_ = nullptr;
    size_t sz_ = 0;
    pair<Node<K, V>*,Node<K, V>*> find_key(K);
    
public:
    MapSet()=default;
    MapSet(initializer_list< Node<K,V> >);
    MapSet (const MapSet&);
    MapSet operator=(MapSet);
    ~MapSet();
    size_t size();
    bool remove (K);
    bool add(Node<K,V>);
    Node<K,V> get(K);
    bool update(K,V);
    int compare(MapSet&);
    MapSet mapset_union (MapSet&);
    MapSet mapset_intersection(MapSet&);
    
    friend ostream& operator<<(ostream &out, const MapSet &ms){//Sends each node to operator<< in Node struct
        ostringstream oss;
        for(auto ptr = ms.head_; ptr != nullptr; ptr = ptr->next){
            oss << *ptr << ", ";
        }
        string s = oss.str();
        out << s.substr(0,s.size()-2);
        return out;
    }
};

/*Initializer_list. Sends each element in list to add and increases sz_ by 1.*/
template<typename K, typename V>
MapSet<K,V>::MapSet(initializer_list< Node<K,V> > il){
    for(Node<K,V> e : il){
        sz_++;
        add(e);
    }
}

/*MapSet copy constructor*/
template<typename K, typename V>
MapSet<K,V>::MapSet(const MapSet &ms){
    if (ms.head_==nullptr){
        head_ = tail_ = nullptr;
        return;
    }
    auto n = new Node<K,V> (*ms.head_);
    head_ = tail_ = n;
    for (auto ptr=ms.head_->next; ptr!=nullptr; ptr=ptr->next){
        n = new Node<K,V> (*ptr);
        tail_->next = n;
        tail_ = n;
    }
}

/*Swaps head_ with the calling MapSet head_ and same with tail_*/
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::operator=(MapSet ms){
    swap(head_, ms.head_);
    swap(tail_, ms.tail_);
    return *this;
}

/*Destructor. Walks down the list, moving head_ (but remember it in to_del). Deletes each node in turn, the set head_ and tail_*/
template<typename K, typename V>
MapSet<K,V>::~MapSet(){
    Node<K,V>* to_del = head_;
    while(to_del != nullptr){
        head_ = head_->next;
        delete to_del;
        to_del = head_;
    }
    head_ = nullptr;
    tail_ = nullptr;
}

/*Returns the size of the MapSet (number of Nodes)*/
template<typename K, typename V>
size_t MapSet<K,V>::size(){
    return sz_;
}

/*Returns two pointers (as a pair). One of the pointers is the lower_bound pointer and the other is the one just
 behind.*/
template<typename K, typename V>
pair<Node<K, V>*,Node<K, V>*> MapSet<K,V>::find_key(K key){
    
    pair<Node<K, V>*,Node<K, V>*> result;
    Node<K,V> *iter, *just_before = nullptr;
    
    for(iter = head_, just_before=nullptr ; iter != nullptr && iter->first != key && iter->first < key ; just_before=iter, iter = iter->next);
    
    return {iter,just_before};
}

/*If the provided node is in the MapSet, do nothing and return false. Otherwise insert the provided node into the list,
 in sorted order, and return true.*/
template<typename K, typename V>
bool MapSet<K,V>::add(Node<K,V> n){
    
    auto pos = find_key(n.first);//pair < iter , just_before >
    
    if(pos.first != nullptr && pos.first->first == n.first){//check if key exists
        return false;
    }
    else{
        if(pos.first == nullptr && pos.second == nullptr){
            Node<K,V>* new_node=new Node<K,V>(n.first,n.second);
            head_ = new_node;
            tail_ = new_node;
            return true;
        }
        
        for(auto x = head_ ; x!=nullptr ; x=x->next){//return false if duplicate
            if(n.first == x->first){
                return false;
            }
        }
        
        if(n.first < head_->first){//add to front
            Node<K,V>* new_node=new Node<K,V>(n.first,n.second);
            new_node->next = head_;
            head_ = new_node;
            return true;
        }
        if(n.first > tail_->first){//add to back
            Node<K,V>* new_node = new Node<K,V>(n.first,n.second);
            tail_->next = new_node;
            tail_ = new_node;
            new_node = nullptr;
            return true;
        }
        else{//add somewhere in middle
            Node<K,V>* new_node=new Node<K,V>(n.first,n.second);
            pos.second->next = new_node;
            new_node->next = pos.first;
            return true;
        }
    }
    return false;
}

/*If the key is in the MapSet, remove the associated Node and return true. If the key
 is not in the MapSet do nothing and return false*/
template<typename K, typename V>
bool MapSet<K,V>::remove(K key){
    auto place = get(key);
    if(place.first == ""){
        return false;
    }
    auto pos = find_key(key);
    if(pos.first == tail_){//remove at end
        pos.second->next = nullptr;
        sz_--;
        delete pos.first;
        return true;
    }
    
    if(pos.second == nullptr){//remove at start
        head_ = head_->next;
        sz_--;
        delete pos.first;
        return true;
    }
    pos.second->next = pos.first->next;//remove in middle
    sz_--;
    delete pos.first;
    return true;
}

/*Returns a Node<K,V> that is either a copy of the Node that has the string as a key or a pair with
 default values ("",0).*/
template<typename K, typename V>
Node<K,V> MapSet<K,V>::get(K key){
    Node<K,V> *x;
    Node<K,V> empty("",0);
    for(x = head_ ; x != tail_->next ; x=x->next){
        if(x->first == key){
            return *x;
        }
    }
    return empty;
}

/*if the key is in the MapSet, update the key-value pair to the value and return true. If the
 key is not in MapSet, do nothing and return false*/
template<typename K, typename V>
bool MapSet<K,V>::update(K key, V value){
    auto pos = get(key);
    
    if(pos.first == ""){
        return false;
    }
    Node<K,V>* new_node=new Node<K,V>(key,value);
    for(auto iter = head_ ; iter!=nullptr ; iter=iter->next){
        if(iter->first == key){
            *iter = *new_node;
            return true;
        }
    }
    return true;
}

/*Compares the two MapSets lexicographically. Comparison is based on the key (string) of each pair. If the argument MapSet is
 greater, return -1. If all of the comparable pairs are equal but one MapSet is larger, then the longer determines the return value
 (1 if the first is longer, -1 if the second)*/
template<typename K, typename V>
int MapSet<K,V>::compare(MapSet &ms){
    
    size_t size1 = ms.sz_, size2 = sz_;
    auto iter1 = nullptr, iter2 = nullptr;
    
    for(auto iter1 = head_ , iter2 = ms.head_ ; iter1 != nullptr && iter2 != nullptr ; iter1=iter1->next, iter2=iter2->next){
        if(iter1->first == iter2->first){
            continue;
        }
        if(iter1->first < iter2->first){
            return -1;
        }
        if(iter1->first > iter2->first){
            return 1;
        }
    }
    if(size2 > size1){
        return 1;
    }
    if(size1 > size2){
        return -1;
    }
    return 0;
}

/*Returns a new MapSet that is a union of the two MapSets being called. Comparison on whether an element is in the MapSet
 is based on the key. If the two MapSets have the same key but different values, then the key-value of the calling MapSet is the
 one that is used*/
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_union(MapSet<K,V> &ms){
    
    MapSet new_ms;
    
    for(auto iter1 = ms.head_ ; iter1!=nullptr ; iter1=iter1->next){
        for(auto iter2 = head_ ; iter2 != nullptr ; iter2=iter2->next){
            if(iter1->first == iter2->first){
                new_ms.add(*iter2);
            }
        }
    }
    for(auto iter1 = ms.head_ ; iter1!=nullptr ; iter1=iter1->next){
        for(auto iter2 = head_ ; iter2!=nullptr ; iter2=iter2->next){
            if(iter1->first != iter2->first){
                new_ms.add(*iter1);
                new_ms.add(*iter2);
            }
        }
    }
    
    return new_ms;
    
}

/*Returns a new MapSet that is the intersection of the two MapSets being called. Comparison on whether an element is in the MapSet
 is based on the key. If the two MapSets have the same key but different values, then the key-value of the calling MapSet is the
 one that is used*/
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_intersection(MapSet<K,V> &ms){
    MapSet new_ms;
    
    for(auto iter1 = ms.head_ ; iter1!=nullptr ; iter1=iter1->next){
        for(auto iter2 = head_ ; iter2!=nullptr ; iter2=iter2->next){
            if(iter1->first == iter2->first){
                new_ms.add(*iter2);
            }
        }
    }
    return new_ms;
}

#endif

