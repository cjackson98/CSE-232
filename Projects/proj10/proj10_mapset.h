/*
Chris Jackson
CSE 232 Project 10
Section 10
Ran out of time to complete project. Put in over 15 hours of work, and made decent progress but was unable to get all the tests to pass. Function/method descriptions specify problems I was encountering and what answers I was getting locally.
*/
#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream; using std::cout; using std::endl;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<algorithm>
using std::sort; using std::lower_bound;
#include<sstream>
using std::ostringstream;
#include <iterator>

//
// Node
//
template<typename K, typename V>
struct Node {
    K first;
    V second;
    Node() = default;
    Node(K,V);
    bool operator<(const Node&) const;
    bool operator==(const Node&) const;
    
    friend ostream& operator<<(ostream &out, const Node &n){//Prints "first:second" to the ostream
        out<<n.first<<":"<<n.second;//////////////////////////////////////////////////////////////////////////////////
        return out;
    }
};

//Constructor
template<typename K, typename V>
Node<K,V>::Node(K key, V value){
    first = key;
    second = value;
}

//Compares two Node instances based on the first values
template<typename K, typename V>
bool Node<K,V>::operator<(const Node &n) const{
    Node x;
    return n.first > x.first;
}

//Two Node instances are equal if their two first values are equal (can't have duplicate keys).
template<typename K, typename V>
bool Node<K,V>::operator==(const Node &n) const{
    Node x;
    return n.first == x.first;
}















//
// MapSet
//
template<typename K, typename V>
class MapSet{
private:
    Node<K,V>* ary_;
    size_t last_;
    size_t capacity_;
    Node<K,V>* find_key(K);
    void grow ();
public:
    MapSet(int sz = 2);
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
    
    friend ostream& operator<<(ostream &out, const MapSet &ms){
        string str;
        ostringstream oss;
        long distance = std::distance(ms.ary_,ms.ary_+ms.last_);
        for(long i = 0 ; i < distance ; i++ ){
            oss<<ms.ary_[i];
            oss<<", ";
        }
        str = oss.str();
        str.pop_back();
        str.pop_back();
        out << str;
        
        return out;
    }
};

//Creates an array of size sz of type Node using the new operator. The sz parameter also is the is the capacity_ of the MapSet. last_ is set to 0.
template<typename K, typename V>
MapSet<K,V>::MapSet(int capacity){
    capacity_=capacity;

    last_=0;
}

//Create an array of size initializer_list.size(). Copy each Node from the list and place in the array.
template<typename K, typename V>
MapSet<K,V>::MapSet(initializer_list< Node<K,V> > il){
    //cout<<"test4"<<endl;
    ary_ = new Node<K,V>[il.size() ];
    for (Node<K,V> e : il){
        add(e);
    }
}

//Constructor
template<typename K, typename V>
MapSet<K,V>::MapSet(const MapSet &ms){
    //cout<<"test3"<<endl;
    capacity_ = ms.capacity_;
    last_ = ms.last_;
    ary_ = new Node<K,V>[capacity_];
    copy(ms.ary_, ms.ary_+ms.last_, ary_);
}

// copy and swap. Seems to occasionally be causing issues with segmentation faults in the union and intersection tests. Specifically when the lines "MapSet<string,long> ms_union = ms1.mapset_union(ms2);" and "MapSet<string,long> ms_intersect = ms1.mapset_intersection(ms2);" run. I modeled this method after the lab12 solution and the 19.7 example provided on the cse232 website.
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::operator=(MapSet<K,V> ms){
    //cout<<"test2"<<endl;
    std::swap(this->capacity_, ms.capacity_);
    std::swap(this->last_, ms.last_);
    std::swap(this->ary_, ms.ary_);
    return *this;
}

//Deconstructor
template<typename K, typename V>
MapSet<K, V>::~MapSet() {
    //delete [] ary_;//Seems to occasionally cause a segmentation fault. Question on Piazza had no answers.
    capacity_=0;
    last_=0;
}

//Size of MapSet (number of nodes). Doesn't work on Mimir, but does locally. No segmentation faults on either my local machine or Mimir IDE. Locally, returns the correct value, on Mimir IDE returns the correct value, but on Mimir tests it does not. Returns 4 instead of 3 for the unhidden test. Posted a question on Piazza and wasn't able to figure it out in time.
template<typename K, typename V>
size_t MapSet<K,V>::size(){
    return last_;
}

//This method doubles the capacity of the underlying array. Creates a new array of twice the capacity, copies the content of the old array into the new, updates capacity_ and ary_, and deletes the old array.
template<typename K, typename V>
void MapSet<K,V>::grow(){
    Node<K,V> *new_ary;
    if (last_ == 0){
        ary_ = new Node<K,V>[1]{};
        capacity_ = 1;
    }
    else{
        new_ary = new Node<K,V>[capacity_ * 2];
        copy(ary_, ary_+capacity_, new_ary);
        capacity_ *= 2;
        ary_=new_ary;
        delete [] new_ary;
    }
}

//Returns a pointer to a Node<K,V> (not an iterator). The pointer is either the first Node in the array that is equal to (by key) or greater than the key, or nullptr.
template<typename K, typename V>
Node<K,V>* MapSet<K,V>::find_key(K key){
    //cout<<key<<endl;
    Node<K,V> holder{key,1};
    Node<K,V>* position = lower_bound(ary_, ary_+last_, holder, [](Node<K,V> n, Node<K,V> search){return (n.first < search.first);});
    //Node<K,V>* position = lower_bound(ary_, ary_+last_, holder, [](Node<K,V> n, Node<K,V> search){return (n.first < search.first);});
    return position;
}

//If the provided node is in the MapSet, do nothing and return false. Otherwise create a Node with the argument values and insert the new pair into the array, in sorted order, and return true.
template<typename K, typename V>
bool MapSet<K,V>::add(Node<K,V> n){
    
    Node<K,V> *new_ary;
    if(last_>=100000000000){
        last_=0;
        capacity_=0;
        if(last_==capacity_){
            grow();
        }
    }
    
    long y = size();
    
    if(y==0){
        grow();
        new_ary = new Node<K,V>[1]{};
        new_ary[0]=n;
        last_++;
        if(last_==capacity_){
            grow();
        }
        ary_=new_ary;
        return true;
    }

    auto position = find_key(n.first);
    if(position == nullptr){
        return false;
    }
    long end = std::distance(ary_,position);
    long size = std::distance(ary_,ary_+last_);
    //cout<<"position->first: "<<position->first<<endl;
    if(end == size){
        new_ary = new Node<K,V>[capacity_]{};
        long ary_dist = std::distance(ary_,ary_+last_);
        for(long num = 0 ; num < ary_dist;num++){
            new_ary[num]=ary_[num];
        }
        new_ary[end]=n;//seg fault = fixed
        ary_=new_ary;
        last_++;//seg fault = fixed
        if(last_==capacity_){
            grow();
        }
        return true;
    }
    if(position->first == n.first){
        return false;
    }
    long x = std::distance(ary_ , position);
    new_ary = new Node<K,V>[capacity_]{};
    for(long num = 0 ; num < x ; num++){
        new_ary[num]=ary_[num];
    }
    new_ary[x]=n;
    
    long distance = std::distance(ary_,ary_+last_);
    for(long num = x ; num <= distance-1 ; num++){
        new_ary[num+1]=ary_[num];
    }
    ary_=new_ary;
    last_++;
    if(last_==capacity_){
        grow();
    }
    ary_=new_ary;
    
    return true;
}

/* if the key is in the MapSet, remove the associated Node and return true. If the key is not in the MapSet do nothing and return false. Hidden test on Mimir doesn't work. Not sure why. In my local testing I was able to remove the first node, the last node, and any node in between all without errors or segmentation fautls. I was also able to attempt to remove a node that was not in the MapSet. */
template<typename K, typename V>
bool MapSet<K,V>::remove(K key){
    Node<K,V> *new_ary;
    
    auto position = find_key(key);
    long distance,ctr=0;
    if(position->first == key){
        distance = std::distance(ary_ , position);
        new_ary = new Node<K,V>[capacity_]{};
        for(long x = 0 ; x < distance ; x++){
            ctr++;
            new_ary[x]=ary_[x];
        }
        if(distance!=last_){
            for(long x = distance+1 ; x <= last_ ; x++){
                ctr++;
                new_ary[x-1]=ary_[x];
            }
        }
        last_--;
        ary_=new_ary;
        return true;
    }
    return false;
}

/*Returns a Node<K,V> that is either a copy of the Node that has the string as a key or a pair with default values*/
template<typename K, typename V>
Node<K,V> MapSet<K,V>::get(K key){
    Node<K,V> x;
    auto position = find_key(key);
    if(position->first == ""){
        x.first = "";
        x.second = 0;
        return x;
    }
    if(position->first == key){
        x.first = position->first;
        x.second = position->second;
        return x;
    }
    x.first = "";
    x.second = 0;
    return x;
}

/*If the key is in the MapSet, update the key-value pair to the value. Return true. If the key is not in MapSet, do nothing and return false.*/
template<typename K, typename V>
bool MapSet<K,V>::update(K key, V value){
    auto position = find_key(key);
    long distance;
    if(position->first==key){
        distance = std::distance(ary_ , position);
        ary_[distance].second=value;
        return true;
    }
    return false;
    
}

/* compare the two MapSets lexicographically using the key of the Nodes as comparison values. If the argument MapSet is greater, return -1. If all o the comparable pairs are equal but one MapSet is larger (has more Nodes), then the longer determines the return value (1 if the first is longer, -1 if the second). Hidden test does not work on Mimir. Not sure why. I've tried to account for both arrays being different lengths, as well as them being the same lengths.*/
template<typename K, typename V>
int MapSet<K,V>::compare(MapSet &ms){
    long dist1= std::distance(ary_ , ary_+last_), dist2= std::distance(ms.ary_ , ms.ary_+ms.last_);
    
    if(dist1>dist2){
        for(long i=0 ; i < dist2 ; i++){
            if(ary_[i].first > ms.ary_[i].first){
                return 1;
            }
            if(ary_[i].first < ms.ary_[i].first){
                return -1;
            }
        }
        return 1;
    }
    if(dist1<dist2){
        for(long i=0 ; i < dist1 ; i++){
            if(ary_[i].first > ms.ary_[i].first){
                return 1;
            }
            if(ary_[i].first < ms.ary_[i].first){
                return -1;
            }
        }
        return -1;
    }
    if(dist1==dist2){
        
        if(ms.ary_ == ary_){
            return 0;
        }
        if(ms.ary_ > ary_){
            return -1;
        }
        if(ms.ary_ < ary_){
            return 1;
        }
    }
    return 0;
}

/*Returns a new MapSet that is a union of the two MapSets being called. Again, comparison on whether an element is in the MapSet is based on the key. If the two MapSets have the same key but different values, then the key-value of the calling MapSet is the one that is used. Seems to randomly get a segmentation fault when constructing ms3. Seems to be caused by ~MapSet function. Adding */
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_union(MapSet<K,V> &ms){
    MapSet<string, long> new_ms;
    
    long end1 = std::distance(ms.ary_,ms.ary_+ms.last_);
    long end2 = std::distance(ary_,ary_+last_);
    
    for(auto i1 = 0 ; i1 < end1 ; i1++){
        for(auto i2 = 0 ; i2 < end2 ; i2++){
            if(ms.ary_[i1].first == ary_[i2].first){
                //cout<<"Add: "<<ary_[i2]<<endl;
                new_ms.add(ms.ary_[i2]);
            }
        }
    }

    for(auto i1 = 0 ; i1 < end1 ; i1++){//When going through this loop at times it will attempt to add a node where the key of that node is already in MapSet, which should add nothing and return false from add();. However, instead it seems to "overrite" the node in MapSet.
        for(auto i2 = 0 ; i2 < end2 ; i2++){
            if(ms.ary_[i1].first != ary_[i2].first){
                //cout<<"1: "<<ary_[i2]<<endl;
                //cout<<"2: "<<ms.ary_[i1]<<endl;
                new_ms.add(ary_[i2]);
                new_ms.add(ms.ary_[i1]);
            }
        }
    }
    
    return new_ms;
}

/*Returns a new MapSet that is the intersection of the two
MapSets being called. Comparison on whether an element is in the MapSet is based on the key. If the two MapSets have the same key but different values, then the key-value of the calling MapSet is the one that is used. Modeled this after my proj09 intersection method. Ran out of time to test.*/
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_intersection(MapSet<K,V> &ms){
    
    MapSet new_ms;
    long end1 = std::distance(ms.ary_,ms.ary_+ms.last_), end2 = std::distance(ary_,ary_+last_);
    
    for(auto i1 = 0 ; i1 < end1 ; i1++){
        for(auto i2 = 0 ; i2 < end2 ; i2++){
            if(ms.ary_[i1].first == ary_[i2].first){
                new_ms.add(ary_[i2]);
            }
        }
    }
    return new_ms;
}


#endif

