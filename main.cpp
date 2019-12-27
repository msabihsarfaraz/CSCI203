#include <time.h>
#include<math.h>
#include<iostream>
#include <stdlib.h>
#include<string>
#include <fstream>
#include<iomanip>
using namespace std;
const int TABLE_SIZE = 2000003;
const int PRIME = 1333331;

/*
 * HashEntry Class Declaration
 */
class HashEntry
{
public:
    long key;
    HashEntry(long key)
    {
        this->key = key;
    }
};

/*
 * HashMap Class Declaration
 */
class HashMap
{
private:
    
public:
    HashEntry **table;
    HashMap()
    {
        table = new HashEntry * [TABLE_SIZE];
        for (int i = 0; i< TABLE_SIZE; i++)
        {
            table[i] = NULL;
        }
    }
    /*
     * Hash Function
     */
    int HashFunc(long key)
    {
        return abs(key % TABLE_SIZE);
    }
    
    /*
     * Insert Element at a key
     */
    void Insert(long key)
    {
        int hash = HashFunc(key);
        if(table[hash] == NULL)
        {
            table[hash] = new HashEntry(key);
            return;
        }
        while (table[hash] != NULL && table[hash]->key != key)
        {
            hash = (hash + 1) % TABLE_SIZE;
        }
        if (table[hash] != NULL)
            delete table[hash];
        table[hash] = new HashEntry(key);
    }
    
    int DoubleHashFunc(long key)
    {
        return abs(PRIME - (key % PRIME));
    }
    
    void InsertDouble(long key)
    {
        int hash = HashFunc(key);
        if(table[hash] == NULL)
        {
            table[hash] = new HashEntry(key);
            return;
        }
        if(table[hash] != NULL && table[hash]->key != key)
        {
            int newHash, j = 0;
            
            do{
                
                j++;
                newHash = (hash + j * DoubleHashFunc(key)) % TABLE_SIZE;
                
            }while(table[newHash] != NULL && table[newHash]->key != key);
            
            if (table[newHash] != NULL)
                delete table[newHash];
            table[newHash] = new HashEntry(key);
        }
    }
    
    void insertLIFO(long key)
    {
        int hash = HashFunc(key);
        if(table[hash] == NULL)
        {
            table[hash] = new HashEntry(key);
            return;
        }
        if (table[hash] != NULL && table[hash]->key != key)
        {
            HashEntry *tempHash = table[hash];
            delete table[hash];
            table[hash] = new HashEntry(key);
            Insert(tempHash->key);
            return;
        }
        if (table[hash] != NULL)
            delete table[hash];
        table[hash] = new HashEntry(key);
    }
    
    int distance(long key, int pos)
    {
        return abs((HashFunc(key) - pos))%TABLE_SIZE;
    }
    
    bool insertBest(long key)
    {
        bool done = false;
        int hash = HashFunc(key);
        if(table[hash] == NULL)
        {
            table[hash] = new HashEntry(key);
            done = true;
        }
        while (table[hash] != NULL && table[hash]->key != key)
        {
            if(distance(table[hash]->key,hash) <= distance(key, hash))
                hash = (hash + 1) % TABLE_SIZE;
            else if(distance(table[hash]->key,hash) > distance(key, hash))
            {
                HashEntry *tempHash = table[hash];
                delete table[hash];
                table[hash] = new HashEntry(key);
                done = true;
                insertBest(tempHash->key);
                break;
            }
        }
        if (table[hash] != NULL)
            delete table[hash];
        table[hash] = new HashEntry(key);
        
        if(done)
            return true;
        else
            return false;
    }
    
    void display()
    {
        for (int i = 1; i <= TABLE_SIZE; i++)
        {
            if (table[i] != NULL)
                cout << i << ": " << table[i]->key << endl;
            else
                cout << i << ": NULL" << endl;
        }
    }
};
/*
 * Main Contains Menu
 */
int main()
{
    HashMap hash1,hash2,hash3;
    long key;
    string line;
    int choice;
    while (1)
    {
        cout<<"1.Insert, first method"<<endl;
        cout <<"2.Insert, second method"<<endl;
        cout<<"3.Insert, third method"<<endl;
        cout<<"4.Display All" << endl;
        cout <<"5.Exit" << endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
            {
                ifstream in("dataset.txt");
                clock_t start = clock();
                // Execuatable code
                while(!in.eof())
                {
                    in >> line;
                    key = atol(line.c_str());
                    hash1.insertLIFO(key);
                }
                clock_t stop = clock();
                double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
                printf("Time elapsed in ms: %f\n", elapsed);
                in.close();
            }
                break;
            case 2:
            {
                ifstream in("dataset.txt");
                clock_t start = clock();
                // Execuatable code
                while(!in.eof())
                {
                    in >> line;
                    key = atol(line.c_str());
                    hash2.InsertDouble(key);
                }
                clock_t stop = clock();
                double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
                printf("Time elapsed in ms: %f\n", elapsed);
                in.close();
            }
                break;
            case 3:
            {
                ifstream in("dataset.txt");
                clock_t start = clock();
                // Execuatable code
                for(int i = 0; i < 1000000;i++)
                {
                    in >> line;
                    key = atol(line.c_str());
                    hash3.insertBest(key);
                }
                clock_t stop = clock();
                double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
                printf("Time elapsed in ms: %f\n", elapsed);
                in.close();
            }
                break;
            case 4:
                for (int i = 0; i < TABLE_SIZE; i++)
                {
                    if (hash1.table[i] != NULL)
                    {
                        cout << i+1 << ": "<< setw(15) << hash1.table[i]->key;
                    }
                    else
                        cout << i+1 << ": "<< setw(15) <<"NULL";
                    if (hash2.table[i] != NULL)
                    {
                        cout << " " << setw(15) << hash2.table[i]->key;
                    }
                    else
                        cout << " " << setw(15) << "NULL";
                    if (hash3.table[i] != NULL)
                    {
                        cout << " " << setw(15) << hash3.table[i]->key << endl;
                    }
                    else
                        cout << " " << setw(15) << "NULL" << endl;
                }
                break;
            case 5:
                exit(1);
            default:
                cout<<"nEnter correct optionn";
        }
    }
    return 0;
}


