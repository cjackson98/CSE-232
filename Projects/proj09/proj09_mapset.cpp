// Chris Jackson
// Section 010
// 4/6/18
// CSE 232 Project 09
#include <iostream>
using std::cout; using std::endl;
#include <sstream>
using std::ostringstream;
#include <string>
using std::to_string;
#include "proj09_mapset.h"

/*Takes each pair and places in the v_ vector. The initializer_list does not have to be in sorted order but the vector should be after after all elements are added.*/
MapSet::MapSet(initializer_list< pair<string,long> > init_pair){
    for(auto iter = init_pair.begin() ; iter!= init_pair.end() ; iter++){
        add(*iter);
    }
}

/*If the string is a in the MapSet (as a key), do nothing and return false. Otherwise, create pair with the provided values and insert it into the vector, in sorted order, and return true.*/
bool MapSet::add(pair<string,long> add_pair){
    MapSet ms;
    if(v_.size()==0){
        v_.push_back(add_pair);
    }
    else{
        for(auto iter=v_.begin() ; iter!=v_.end() ; iter++){
            if(iter->first == add_pair.first){
                return false;
            }
            if(iter->first > add_pair.first){
                v_.insert(iter, add_pair);
                //ms = v_;
                return true;
            }
            else if(iter->first < add_pair.first){
                continue;
            }
        }
        v_.insert(v_.end(), add_pair);
        
        return true;
    }
    return true;
}

/*Uses lower_bound to return an iterator to a pair<string,long> that is either the first pair in the vector equal to (by key), or greather than the key, or v_.end().  */
vector< pair <string, long> >::iterator MapSet::find_key(string key){
    
    vector<pair<string,long>>::iterator itr = lower_bound(v_.begin(), v_.end(), key, [](pair<string,long> p1, string str)
    {
    cout<<"Test: "<<p1.first<<", "<<str<<endl;
        if(p1.first==str){
            return false;
        }
        else{
            return true;
        }
        });
    
    return itr;
}

/*Returns the ostream after writing MapSet to it. Formatted as key1:value1, key2:value2, etc.*/
ostream& operator<<(ostream& out, MapSet& ms){//"alan:2, bill:1, fred:3"
    if ( ms.v_.empty() )
        out << "Empty";
    else{
        ostringstream oss;
        for(auto iter = ms.v_.begin() ; iter!=ms.v_.end() ; iter++){
            oss<<iter->first<<":"<<iter->second<<", ";
        }
        string str = oss.str();
        str.pop_back();
        str.pop_back();
        out << str;
    }
    return out;
}

/*Returns the size of the MapSet (number of pairs)*/
size_t MapSet::size(){
    size_t size = v_.size();
    return size;
}

/*Returns a pair<string,long> that is either a copy of the pair that has a key that matchces the provided string, or a pair with the default values ({"",0}).*/
pair<string,long> MapSet::get(string key){
    pair<string,long> empty = {"",0};
    for(auto iter = v_.begin() ; iter!=v_.end() ; iter++){
        if(iter->first == key){
            return *iter;
        }
    }
    return empty;
}

/*If the string matches a key in the MapSet, updates the value of that key to the value of the provided long and returns true. Otherwise, returns false.*/
bool MapSet::update(string key,long val){
    for(auto iter = v_.begin() ; iter!=v_.end() ; iter++){
        if(iter->first == key){
            iter->second=val;
            return true;
        }
    }
    return false;
}

/*If the string matches a key in the MapSet, removes the associated pair and returns true. Otherwise, returns false.*/
bool MapSet::remove(string key){
    for(auto iter = v_.begin() ; iter!=v_.end() ; iter++){
        if(iter->first == key){
            v_.erase(iter);
            return true;
        }
    }
    
    return false;
}

/*Compares two MapSets lexicographically. The first difference found between the two will determine the return value. If the calling MapSet is greater, returns 1. If the argument MapSet is greater, returns -1. If all of the keys are equal but one MapSet is larger, the larger MapSet will determine the return value. Returns 1 if the first is larger, -1 if the second is larger.*/
int MapSet::compare(MapSet& ms){
    
    size_t size1 = ms.v_.size(),size2 = v_.size();
    
    if(size1>size2){
        for(long i=0 ; i < size2 ; i++){
            if(v_[i].first > ms.v_[i].first){
                return 1;
            }
            if(v_[i].first < ms.v_[i].first){
                return -1;
            }
        }
        return -1;
    }
    if(size1<size2){
        for(long i=0 ; i < size1 ; i++){
            if(v_[i].first > ms.v_[i].first){
                return 1;
            }
            if(v_[i].first < ms.v_[i].first){
                return -1;
            }
        }
        return 1;
    }
    if(size1==size2){
        
        if(ms.v_ == v_){
            return 0;
        }
        if(ms.v_ > v_){
            return -1;
        }
        if(ms.v_ < v_){
            return 1;
        }
    
    }
    return 0;
}

/*Returns a new MapSet that is the union of the two MapSets being called. Comparison based on the keys. If the two MapSets have the same key but different values, then the value of the calling MapSet is the one used.*/
MapSet MapSet::mapset_union (MapSet& ms){
    MapSet new_ms;
    
    for(auto iter1 = ms.v_.begin() ; iter1!=ms.v_.end() ; iter1++){
        for(auto iter2 = v_.begin() ; iter2!=v_.end() ; iter2++){
            if(iter1->first == iter2->first){
                new_ms.add(*iter2);
            }
        }
    }
    for(auto iter1 = ms.v_.begin() ; iter1!=ms.v_.end() ; iter1++){
        for(auto iter2 = v_.begin() ; iter2!=v_.end() ; iter2++){
            if(iter1->first != iter2->first){
                new_ms.add(*iter1);
                new_ms.add(*iter2);
            }
        }
    }

    return new_ms;
}

/*Returns a new MapSet that is the intersection of the two MapSets being called. Comparison based on the keys. If the two MapSets have the same key but different values, then the value of the calling MapSet is the one used.*/
MapSet MapSet::mapset_intersection(MapSet& ms){
    MapSet new_ms;

    for(auto iter1 = ms.v_.begin() ; iter1!=ms.v_.end() ; iter1++){
        for(auto iter2 = v_.begin() ; iter2!=v_.end() ; iter2++){
            if(iter1->first == iter2->first){
                new_ms.add(*iter2);
            }
        }
    }
    return new_ms;
}
