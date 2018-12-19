#include <iostream>
using std::domain_error; using std::invalid_argument;
#include <set>
using std::set;
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <utility>
using std::pair;
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <strstream>

#include "proj07_functions.h"

/*
 This function tries to connect the specified user to the specifiec server. If the server exists, it adds the user to that
 server. If the server does not exist, it is created and the user is added to that server.
 If the user is already connected to the server , then no action is taken.
*/
bool AddConnection(ServerData &sd, ServerName sn, UserName un){
    ServerData::iterator sn_iter;
    sn_iter = sd.find(sn);
    set<string>::iterator set_iter;
    set<string> user_set;

    if(sn_iter != sd.end()){//if the server DOES exist
        user_set=sn_iter->second;
        set_iter=user_set.find(un);
        if(set_iter == user_set.end()){//if the server DOES exist in the map and the user DOES NOT exist in the server
            user_set.insert(un);
            sd[sn] = user_set;
            return true;
        }
        else
            return false;
    }
    else{//if the server DOES NOT exist
        user_set.insert(un);//set<string> user_set{un};
        sd[sn] = user_set;
        return true;
    }
    return false;
}

/*
 This function tries to disconnect the specified user from the specified server, and returns true if this is possible.
 If the user is not connected to the server, then no action is taken, and the function returns false.
*/
bool DeleteConnection(ServerData &sd, ServerName sn, UserName un){
    ServerData::iterator sn_iter;
    sn_iter = sd.find(sn);
    set<string>::iterator set_iter;
    set<string> user_set;
    
    if(sn_iter != sd.end()){//if the server DOES exist
        user_set=sn_iter->second;
        set_iter=user_set.find(un);
        if(set_iter == user_set.end()){//if the server DOES exist in the map and the user DOES NOT exist in the server
            return false;
        }
        else{
            user_set.erase(un);
            sd[sn]=user_set;
            return true;
        }
    }
    else
        return false;
}

/*
 For each line in the provided file (fname), if the 2nd word is join, then add the specified username (1st word) to
 the specified server (3rd word). If the 2nd string is leave, then remove the specified username (1st word) from
 the specified server (3rd word). If specified action cannot be performed, e.g. if trying to add user to
 server when user is already connected to the server, then that action is simply ignored.
*/
ServerData ParseServerData(const std::string &fname){
    
    ServerData sd;
    
    ifstream file(fname);
    string str1,str2,str3;
    if(file)
    {
        while (!file.eof())
        {
            file >> str1 >> str2 >> str3;
            if(str2!="leave" && str2!="join"){
                throw domain_error("Invalid command");
            }
            if(str2=="join"){
                AddConnection(sd, str3, str1);
            }
            else if(str2=="leave"){
                DeleteConnection(sd, str3, str1);
            }
        }
    }
    else
        throw invalid_argument("Couldn't open file");
    
    return sd;
}

/*
 Prints the contents of sd to out (not cout, but the passed ostream out)
*/
void PrintAll(std::ostream &out, const ServerData &sd){
    string all_users,user;
    set<string> user_set1;
    
    for(ServerData::const_iterator iter1 = sd.begin(); iter1 != sd.end(); iter1++) {//make a set of users for sn1
        user_set1 = iter1->second;
        string server = iter1->first;
        all_users.clear();
        for (set<string>::iterator iter2 = user_set1.begin() ; iter2 != user_set1.end(); iter2++)
        {
            user = *iter2;
            all_users.append(user+" ");
        }
        all_users.pop_back();
        out << server <<" : "<< all_users << '\n';
    }
}

/*
Returns a set<string> which is the set of all servers in the sd
*/
set<string> AllServers(const ServerData &sd){
    set<string> servers;
    
    for(ServerData::const_iterator it = sd.begin(); it != sd.end(); ++it) {
        servers.insert(it->first);
    }
    
    return servers;
}

/*
 Returns a set<string> which is the set of all users on any server in sd
*/
set<string> AllUsers(const ServerData &sd){
    //Returns a set<string> which is the set of all users on any server in the sd
    set<string> total_user_set,user_set;
    
    for(ServerData::const_iterator iter = sd.begin(); iter != sd.end(); iter++) {
        user_set = iter->second;
        for (set<string>::iterator iter2 = user_set.begin() ; iter2 != user_set.end(); iter2++)
        {
            string user = *iter2;
            total_user_set.insert(user);
        }
    }
    
    return total_user_set;
}

/*
 This function returns a set<string> of all the server names in sd that the specified user is
 currently connected to. The return set could be empty.
*/
set<string> HasConnections(const ServerData &sd, UserName un){
    set<string> total_user_set,user_set,connected_servers;
    string sn;
    
    for(ServerData::const_iterator iter = sd.begin(); iter != sd.end(); iter++) {
        user_set = iter->second;
        for (set<string>::iterator iter2 = user_set.begin() ; iter2 != user_set.end(); iter2++)
        {
            string user = *iter2;
            if(*iter2==un){
                sn = iter->first;
                connected_servers.insert(sn);
            }
        }
    }
    
    return connected_servers;
}

/*
 This function returns a set<string> of all the users currently connected to the specified server. The return set could be empty.
*/
set<string> HasUsers(const ServerData &sd, ServerName sn){
    set<string> total_user_set,user_set,connected_users;
    string user;
    
    for(ServerData::const_iterator iter = sd.begin(); iter != sd.end(); iter++) {
        user_set = iter->second;
        if(iter->first == sn){
            for (set<string>::iterator iter2 = user_set.begin() ; iter2 != user_set.end(); iter2++)
            {
                user = *iter2;
                connected_users.insert(user);
            }
        }
    }

    return connected_users;
}

/*
 This function tries to balance the number of users that are connected to specified servers sn1 and sn2. If a
 user is connected to both servers, then they are not moved. All the users that are only connected
 to one of the 2 servers are sorted alphabetically by their name, and the first half are moved to
 server sn1, and the other half are moved to server sn2.
 (if there are an odd number N of users, then N/2 +1 users are moved to sn1 and the remaining are moved to sn2)
*/
void BalanceServers(ServerData &sd, ServerName sn1, ServerName sn2){
    set<string>::iterator iter;
    set<string> sn1_users = HasUsers(sd, sn1),sn2_users = HasUsers(sd, sn2), unique_users, same_users;
    long size,n;
    string user;
    
    for(set<string>::iterator iter1 = sn1_users.begin() ; iter1 != sn1_users.end() ; iter1++){
        unique_users.insert(*iter1);
    }
    for(set<string>::iterator iter2 = sn2_users.begin() ; iter2 != sn2_users.end() ; iter2++){
        unique_users.insert(*iter2);
    }
    
    for(set<string>::iterator iter1 = sn1_users.begin() ; iter1 != sn1_users.end() ; iter1++){
        for(set<string>::iterator iter2 = sn2_users.begin() ; iter2 != sn2_users.end() ; iter2++){
            if(*iter1==*iter2){
                unique_users.erase(*iter1);
                same_users.insert(*iter1);
            }
        }
    }
    sn1_users=same_users;
    sn2_users=same_users;

    size = unique_users.size();
    if(size%2==0){
        n=size/2;
    }
    else{
        n=size/2+1;
    }

    iter = unique_users.begin();
    while(n>0){
        user = *iter;
        sn1_users.insert(user);
        n--;
        iter++;
        unique_users.erase(user);
    }
    
    for(set<string>::iterator iter = unique_users.begin() ; iter != unique_users.end() ; iter++){
        user=*iter;
        sn2_users.insert(user);
    }
    
    for(ServerData::iterator iter = sd.begin() ; iter != sd.end() ; iter++){
        if(iter->first==sn1){
            sd[sn1]=sn1_users;
        }
        if(iter->first==sn2){
            sd[sn2]=sn2_users;
        }
    }
}

/*
 This function first removes all duplicate users from sd. Then the unique users are moved as follows:
 1. All the user names and server names are sorted alphabetically
 2. The users are distributed to servers in a round-robin fashion in alphabetical order of
 server and user names.
*/
void CleanAndBalance(ServerData &sd){
    set<string> used_users, all_servers = AllServers(sd), all_users, users;
    string sn;
    
    for(ServerData::iterator iter1 = sd.begin() ; iter1 != sd.end() ; iter1++){
        set<string> users = iter1->second;
        for(set<string>::iterator iter2 = users.begin() ; iter2 != users.end() ; iter2++){
            for(set<string>::iterator iter3 = used_users.begin() ; iter3 != used_users.end() ; iter3++){
                if(*iter2==*iter3){
                    users.erase(*iter2);
                }
                else{
                    used_users.insert(*iter2);
                }
            }
        }
    }
    all_servers = AllServers(sd);
    all_users = AllUsers(sd);

    for(set<string>::iterator iter = all_servers.begin() ; iter != all_servers.end() ; iter++){
        sd[*iter].clear();
    }
    
    while(all_users.size()!=0){
        for(set<string>::iterator iter = all_servers.begin() ; iter != all_servers.end() ; iter++){
            sn = *iter;
            
            if(all_users.size()>0){
                sd[sn].insert(*all_users.begin());
                all_users.erase(all_users.begin());
            }
        }
    }
}
