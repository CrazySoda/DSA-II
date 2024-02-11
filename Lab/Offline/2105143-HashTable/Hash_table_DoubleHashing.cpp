#include <bits/stdc++.h>
using namespace std;
const long long HASH_MOD = 1'000'000'007; // very big prime number

// populate an array filled with only unique words and delete the duplicate ones
//  Function to generate random words
vector<string> generate_words(int n)
{
    vector<string> words;
    for (int i = 0; i < n; i++)
    {
        string word = "";
        int len = 5 + rand() % 6;
        for (int j = 0; j < len; j++)
        {
            word += 'a' + rand() % 26;
        }
        words.push_back(word);
    }
    return words;
}
vector<string> select_random_words(const vector<string> &generated_words, int amount)
{
    vector<string> selected_words;
    int n = generated_words.size();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, n - 1);
    for (int i = 0; i < amount; ++i)
    {
        int random_index = dis(gen);
        selected_words.push_back(generated_words[random_index]);
    }

    return selected_words;
}
// Function to remove duplicates from the vector
void remove_duplicates(vector<string> &words)
{
    unordered_set<string> unique_words(words.begin(), words.end());
    words.assign(unique_words.begin(), unique_words.end());
}
// generate unique words
vector<string> generate_unique_words(int n)
{
    vector<string> words;
    while (words.size() < n + 1)
    {
        int remaining = n + 1 - words.size();
        int batch_size = min(remaining, 5);
        vector<string> new_words = generate_words(batch_size);
        new_words.erase(remove(new_words.begin(), new_words.end(), ""), new_words.end());
        words.insert(words.end(), new_words.begin(), new_words.end());
        // Remove duplicates
        remove_duplicates(words);
    }

    return words;
}
void show_generated_words_with_index(vector<string> &words)
{
    for (int i = 0; i < words.size(); i++)
    {
        cout << i << ": " << words[i] << endl;
    }
}

// check if it is prime
bool is_prime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}
// generate the next prime
int next_prime(int prime)
{
    int next = prime + 1;
    while (!is_prime(next))
    {
        next++;
    }
    return next;
}
// Hash Function from a good source
uint32_t Hash1(const string &s, int mod)
{
    // djb2 hash function by Dan Bernstein
    // http://www.cse.yorku.ca/~oz/hash.html
    long long hash = 5381; // keep this large then if the table length is increased it will generate different result
    for (auto &c : s)
    {
        hash = (((hash << 5) + (hash)) + c); // valid
    }
    return (uint32_t)hash;
}
uint32_t Hash(const string &key, int N)
{
    // Jenkins One At a Time Hash
    // http://en.wikipedia.org/wiki/Jenkins_hash_function

    uint32_t hash = 0;
    for (char c : key)
    {
        hash += c;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}
uint32_t auxHash(const string &key, int N)
{
    // Source: https://stackoverflow.com/a/21001712
    unsigned int byte, crc, mask;
    int i = 0, j;
    crc = 0xFFFFFFFF;
    for (unsigned char c : key)
    {
        byte = c;
        crc = crc ^ byte;
        for (j = 7; j >= 0; j--)
        {
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
        i = i + 1;
    }
    return (~crc);
}
// Hash Table
class HashTable
{
public:
    int size;
    int no_of_elements;
    int no_of_collisions;
    vector<pair<string, int>> table;
    HashTable(int size)
    {
        this->no_of_collisions= 0;
        this->no_of_elements = 0;
        this->size = size;
        table.resize(next_prime(size));
        cout << table.size() << endl;
        cout << "table created" << endl;
    }
    ~HashTable(){
        cout<<"HashTable destroyed"<<endl;
    }
    uint32_t doubleHash(const string &key, int i, int N, uint32_t (*Hash)(const string &, int)) const
    {
        return (Hash(key, N) + i * auxHash(key, N)) % N;
    }
    void insert(const string &key, int value,uint32_t (*Hash)(const string &, int))
    {
        //cout << "inserting" << endl;
        if (no_of_elements == size)
        {
            cout << "Skipping insertion for key: " << key << ", as the table is filled." << endl;
            return;
        }
        int index;
        for (int i = 0; i < size; i++)
        {
            index = doubleHash(key, i, size, Hash);
            if (table[index].first.empty())
            {
                table[index].first = key;
                table[index].second = value;
                no_of_elements++;
                return;
            }else no_of_collisions++;
        }
    }

    void insert(const vector<string> &words,uint32_t (*Hash1)(const string &, int))
    {
        for (int i = 0; i < words.size(); ++i)
        {
            insert(words[i], i,Hash1);
        }
    }

    int search(const string key,uint32_t (*Hash)(const string &, int)) const
    {
        int no_of_probs = 0;
        cout << "searching" << endl;
        int index, i;
        for (i = 0; i < size; ++i)
        {
            index = doubleHash(key, i, size, Hash);
            if (table[index].first == key)
                break;
            if (i == size)
            {
                cout << "Key '" << key << "' not found in the hash table." << endl;
                return 0;
            }
        }
        no_of_probs += i + 1;
        return no_of_probs;
    }
    double averageProbing(const vector<string> &selected_words, uint32_t (*Hash)(const string &,int)) const {
        int total_probes = 0;
        for (const string &word : selected_words) {
            int probe = search(word,Hash);
            total_probes += probe;
        }
        double average_probe = static_cast<double>(total_probes) / selected_words.size();
        return average_probe;
    }
    void delete_key(const string &key,uint32_t (*Hash)(const string &, int))
    {
        int index;
        for (int i = 0; i < size; ++i)
        {
            index = doubleHash(key, i, size, Hash);
            if (table[index].first == key)
                break;
            if (i == size)
            {
                cout << "Key '" << key << "' not found in the hash table." << endl;
                return ;
            }
        }
        table[index].first = "";
        table[index].second = 0;
        //cout<<"Key deleted"<<endl;
    }
    void delete_words(const vector<string> &words, uint32_t (*Hash)(const string &, int))
    {
        for (const string &word : words)
        {
            delete_key(word,Hash);
        }
    }


    void show()
    {
        for (int i = 0; i < size; i++)
        {
            cout << i << ": " << table[i].first << " " << table[i].second << endl;
        }
    }
};

int main()
{
    freopen("output_dh.txt", "w", stdout);
    HashTable ht(5000);
    vector<string> words = generate_unique_words(10000);
    vector<string> selected_words = select_random_words(words, 1000);
    vector<string> to_dlt_words = select_random_words(words, 1000);
    cout << "Generated words: \n";
    show_generated_words_with_index(words);
    ht.insert(words,Hash);
    int avgprob = ht.averageProbing(selected_words,Hash);
    cout << "Average Probes: " << avgprob << endl;
    cout << "Hash Table: \n";
    cout<<"Maximum Collisions: "<<ht.no_of_collisions<<"\n";
    ht.delete_words(to_dlt_words,Hash);
    ht.show();
    return 0;
}