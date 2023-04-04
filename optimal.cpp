#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <assert.h>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) // Don't forget first integral argument 'argc'
{
  string current_exec_name = argv[0]; // Name of the current exec program
  vector<string> all_args;
  assert(argc==4);   
  all_args.assign(argv + 1, argv + argc);
   
  //std::cout<< " Size "<<all_args.size()<<"\n";
  //assert(0);
    string replPolicy = all_args[0];
    int compulsory_misses =0, capacity_misses =0,total_accesses=0,hits=0;
    ifstream inFile(all_args[1].c_str());
     int numberOfCacheEntries = stoi(all_args[2]);
    if (inFile.is_open())
    {
         cout<<" Opened input file "<<all_args[1]<<"\n";
         
        vector<string> cache_future;
        vector<string> cache;
        int i=0;
       
        while(!inFile.eof())
        {
            string x;
            inFile >> x;
            remove(x.begin(), x.end(), ' ');
            if(x.empty())
                continue;
            cache_future.push_back(x);
            total_accesses++;
        }
        while(i!=cache_future.size())
        {
             bool found=false;
             bool breakV=false;
            string x= cache_future[i];
            int maxI=0,cacheI=0;
            if(cache.size()!=0)
            {
                for(int j=0;j<cache.size();j++)
                {
                    if(cache[j]==x)
                    {
                        cout<<"HIT"<<endl;
                        hits++;
                        found=true;
                        break;
                    }
                }
                if(!found)
                {
                    for(int j=0;j<i;j++)
                    {
                        if(x==cache_future[j])
                        {
                            cout<<"MISS"<<endl;
                            capacity_misses++;
                            found=true;
                            break;
                        }                    
                    }
                    if(found)
                    {
                        for(int j=0;j<cache.size();j++)
                        {
                            for(int k=i+1;k<cache_future.size();k++)
                            {
                                if(cache[j]==cache_future[k])
                                {
                                    
                                    if(k>=maxI)
                                    {
                                    maxI=k;
                                    cacheI=j;
                                    }
                                    break;
                                }
                                if(k+1==cache_future.size())
                                {
                                     if(cache[j]!=cache_future[k])
                                    {
                                        maxI=k;
                                        cacheI=j;
                                        breakV=true;
                                        break;
                                    }
                                }

                            }
                            if(breakV)
                            {
                                breakV=false;
                                break;
                            }
                        }   
                        
                            if(cache.size()<numberOfCacheEntries)
                            cache.push_back(x);
                            else
                            cache[cacheI]=x;
                        
                    } 
                }
                if(!found)
                {
                    cout<<"MISS"<<endl;
                    compulsory_misses++;
                     if(cache.size()<numberOfCacheEntries)
                            cache.push_back(x);
                     else    
                     {
                         for(int j=0;j<cache.size();j++)
                        {
                            for(int k=i+1;k<cache_future.size();k++)
                            {
                                if(cache[j]==cache_future[k])
                                {
                                    
                                    if(k>=maxI)
                                    {
                                    maxI=k;
                                    cacheI=j;
                                    }
                                    break;
                                }
                                if(k+1==cache_future.size())
                                {
                                     if(cache[j]!=cache_future[k])
                                    {
                                        maxI=k;
                                        cacheI=j;
                                        breakV=true;
                                        break;
                                    }
                                }

                            }
                            if(breakV){
                                breakV=false;
                                break;
                            }
                        }   
                        cache[cacheI]=x;
                    }
                     
                        
                }
            }
                
            
            else{
                compulsory_misses++;
                cout <<"MISS"<< endl;
                cache.push_back(x);
            }
            i++;
           /*vector<string> cache_state;
            cache_state = cache;
            for(int a=0;a<cache_state.size();a++)
            cout<<cache_state[a]<<" ";

        
            cout<<" "<<endl;*/
        
        }
        
    
    }
    
    else { //Error message
        cerr << "Can't find input file " <<  endl;
        assert(0);
    }
    cout<<" total_accesses "<<total_accesses <<"\n";
    cout<<" numberOfCacheEntries "<<numberOfCacheEntries <<"\n";
    cout<<" replPolicy = "<<replPolicy<<"\n";
    cout<<" compulsory misses = "<<compulsory_misses<<"\n";
    cout<<" capacity misses = "<<total_accesses-hits-compulsory_misses<<"\n";
    cout<<" total misses = "<<total_accesses-hits<<"\n";
    inFile.close(); // Close input file
    
}
 
