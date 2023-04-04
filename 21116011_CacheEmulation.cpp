#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <assert.h>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) // Don't forget first integral argument 'argc'
{
  string current_exec_name = argv[0]; // Name of the current exec program
  vector<string> all_args;
  assert(argc == 4);
  all_args.assign(argv + 1, argv + argc);

 
  string replPolicy = all_args[0];

  int compulsory_misses = 0, capacity_misses = 0, total_accesses = 0;
  ifstream inFile(all_args[1].c_str());
  int numberOfCacheEntries = stoi(all_args[2]);
  size_t lastindex = all_args[1].find_last_of(".");
  string rawname = all_args[1].substr(0, lastindex);

  vector<string> hit_miss;
  if (inFile.is_open())
  {
    cout << " Opened input file " << all_args[1] << "\n"
         << "Processing...Please wait"
         << "\n";
    if (replPolicy == "LRU")
    {
      deque<string> cache;
      vector<string> cache_history;

      while (!inFile.eof())
      {
        total_accesses++;
        string x;
        inFile >> x;
        remove(x.begin(), x.end(), ' ');
        if (x.empty())
          continue;
        cache_history.push_back(x);
        bool found = false;

        deque<string>::iterator fi = find(cache.begin(), cache.end(), x);
        for (int i = 0; i < cache_history.size() - 1; i++)
        {
          if (cache_history[i] == x)
          {
            found = true;
          }
        }

        if (!cache.empty())
        {
          if (fi != cache.end() || x == cache.back())
          {
            hit_miss.push_back("HIT");
            cache.push_front(x);

            if (x == cache.back())
              cache.pop_back();
            else
            {
              deque<string> revCache;
              revCache = cache;
              revCache.pop_front();
              do
              {
                cache.pop_back();
              } while (cache.back() != x);
              cache.pop_back();
              while (revCache.front() != x)
                revCache.pop_front();
              revCache.pop_front();

              while (revCache.size() != 0)
              {
                string element = revCache.front();
                cache.push_back(element);
                revCache.pop_front();
              }
            }
          }
          else if (found)
          {

            hit_miss.push_back("MISS");
            capacity_misses++;
            cache.push_front(x);
            if (cache.size() > numberOfCacheEntries)
              cache.pop_back();
          }
          else
          {
            hit_miss.push_back("MISS");
            compulsory_misses++;
            cache.push_front(x);
            if (cache.size() > numberOfCacheEntries)
              cache.pop_back();
          }
        }
        else
        {
          hit_miss.push_back("MISS");
          compulsory_misses++;
          cache.push_front(x);
        }
      }
    }
    else if (replPolicy == "OPTIMAL")
    {
      vector<string> cache_future;
      vector<string> cache;
      int i = 0;

      while (!inFile.eof())
      {
        string x;
        inFile >> x;
        remove(x.begin(), x.end(), ' ');
        if (x.empty())
          continue;
        cache_future.push_back(x);
        total_accesses++;
      }
      while (i != cache_future.size())
      {
        bool found = false;
        bool breakV = false;
        string x = cache_future[i];
        int maxI = 0, cacheI = 0;
        if (cache.size() != 0)
        {
          for (int j = 0; j < cache.size(); j++)
          {
            if (cache[j] == x)
            {
              hit_miss.push_back("HIT");
              found = true;
              break;
            }
          }
          if (!found)
          {
            for (int j = 0; j < i; j++)
            {
              if (x == cache_future[j])
              {
                hit_miss.push_back("MISS");
                capacity_misses++;
                found = true;
                break;
              }
            }
            if (found)
            {
              for (int j = 0; j < cache.size(); j++)
              {
                for (int k = i + 1; k < cache_future.size(); k++)
                {
                  if (cache[j] == cache_future[k])
                  {

                    if (k >= maxI)
                    {
                      maxI = k;
                      cacheI = j;
                    }
                    break;
                  }
                  if (k + 1 == cache_future.size())
                  {
                    if (cache[j] != cache_future[k])
                    {
                      maxI = k;
                      cacheI = j;
                      breakV = true;
                      break;
                    }
                  }
                }
                if (breakV)
                {
                  breakV = false;
                  break;
                }
              }

              if (cache.size() < numberOfCacheEntries)
                cache.push_back(x);
              else
                cache[cacheI] = x;
            }
          }
          if (!found)
          {
            hit_miss.push_back("MISS");
            compulsory_misses++;
            if (cache.size() < numberOfCacheEntries)
              cache.push_back(x);
            else
            {
              for (int j = 0; j < cache.size(); j++)
              {
                for (int k = i + 1; k < cache_future.size(); k++)
                {
                  if (cache[j] == cache_future[k])
                  {

                    if (k >= maxI)
                    {
                      maxI = k;
                      cacheI = j;
                    }
                    break;
                  }
                  if (k + 1 == cache_future.size())
                  {
                    if (cache[j] != cache_future[k])
                    {
                      maxI = k;
                      cacheI = j;
                      breakV = true;
                      break;
                    }
                  }
                }
                if (breakV)
                {
                  breakV = false;
                  break;
                }
              }
              cache[cacheI] = x;
            }
          }
        }

        else
        {
          compulsory_misses++;
          hit_miss.push_back("MISS");
          cache.push_back(x);
        }
        i++;
      }
    }

    else
      cout << "INVALID REPLACEMENT POLICY" << endl;
  }

  else
  { // Error message
    cerr << "Can't find input file " << endl;
    assert(0);
  }
  string fileName = "21116011_" + replPolicy + "_" + rawname + "_" + all_args[2] + ".out";
  ofstream MyFile(fileName);
  cout << "Completed Processing and made output file" << endl;
  MyFile << " TOTAL_ACCESSES " << total_accesses << "\n";
  MyFile << " TOTAL_MISSES = " << capacity_misses + compulsory_misses << "\n";
  MyFile << " COMPULSORY_MISSES = " << compulsory_misses << "\n";
  MyFile << " CAPACITY_MISSES = " << capacity_misses << "\n";

  for (int f = 0; f < hit_miss.size(); f++)
    MyFile << hit_miss[f] << endl;
  inFile.close();
  MyFile.close();
}
