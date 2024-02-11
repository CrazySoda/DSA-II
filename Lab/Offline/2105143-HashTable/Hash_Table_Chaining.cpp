#include <memory>
#include <bits/stdc++.h>
using namespace std;
vector<string> input_words;

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
// Hash Function from a good source
uint32_t Hash1(const string &s, long long mod)
{
    // djb2 hash function by Dan Bernstein
    // http://www.cse.yorku.ca/~oz/hash.html
    long long hash = 5381; // keep this large then if the table length is increased it will generate different result
    for (auto &c : s)
    {
        hash = (((hash << 5) + (hash)) + c) % mod; // valid
    }
    return (uint32_t)hash;
}
uint32_t Hash(const string &key, int N) {
    // Jenkins One At a Time Hash
    // http://en.wikipedia.org/wiki/Jenkins_hash_function

    uint32_t hash = 0;
    for (char c : key) {
        hash += c;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash % N;
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

class HashTable
{
public:
    vector<list<pair<string, int>>> table;
    int max_bucket_size;
    int size;
    int no_of_elements;
    int average_probes;
    int erase_count = 0;
    int limit;
    HashTable(int max_bucket_size, int size)
    {
        limit = size;
        // cout<<"size: "<<this->size<<endl;
        this->size = next_prime(size);
        this->max_bucket_size = max_bucket_size;
        // cout<<"max_bucket_size: "<<this->max_bucket_size<<endl;
        table.resize(this->size);
        this->no_of_elements = 0;
        // cout<<"table size:"<<table.size()<<endl;
        // cout<<"hash_table created"<<endl;
    }
    ~HashTable()
    {
        cout << "hash_table destroyed" << endl;
    }

    void insert(const vector<string> &words)
    {

        for (int i = 1; i < words.size(); ++i)
        {
            insert(words[i], i);
            // cout<<"inserted"<<endl;
            if (i % 100 == 0)
            {
                int max_size = size_of_longest_chain();
                // cout<<"max_size before rehashing: "<<max_size<<endl;
                while (max_size > max_bucket_size)
                {
                    cout << "rehashing" << endl;
                    rehash(2);
                    max_size = size_of_longest_chain();
                }
                // cout<<"max_size after rehashing: "<<max_size<<endl;
            }
        }
    }
    void rehash(double n)
    {
        cout << "max_bucket_size before rehashing: " << size_of_longest_chain() << endl;
        int new_size = size * n;
        vector<list<pair<string, int>>> new_table(new_size);
        for (int i = 0; i < size; i++)
        {
            for (auto &p : table[i])
            {
                int index = Hash(p.first, new_size);
                new_table[index].push_back(p);
            }
        }
        this->table = move(new_table);
        this->size = new_size;
        cout << "max_bucket_size after rehashing: " << size_of_longest_chain() << endl;
    }
    void insert(const string &s, int index)
    {
        int hash_index = Hash(s, size);
        // cout<<"hash_index: "<<hash_index<<endl;
        table[hash_index].push_back({s, index});
        no_of_elements++;
    }
    int size_of_longest_chain()
    {
        int max_size = 0;
        for (int i = 0; i < size; i++)
        {
            max_size = max(max_size, (int)table[i].size());
        }
        return max_size;
    }

    void erase_all(const vector<string> &strings_to_erase)
    {
        for (const string &s : strings_to_erase)
        {
            erase(s);
        }
    }

    void erase(const string &s)
    {
        int index = Hash(s, size);
        for (auto it = table[index].begin(); it != table[index].end(); it++)
        {
            if (it->first == s)
            {
                table[index].erase(it);
                no_of_elements--;
                erase_count++;
                if (erase_count % 100 == 0)
                {
                    int longest_chain_length = size_of_longest_chain();
                    // double load_factor = (double)no_of_elements / size;
                    do
                    {
                        if (longest_chain_length < 0.8 * this->max_bucket_size)
                        {

                            rehash(0.5);
                        }
                    } while (this->size > limit);
                }
                cout << "Element erased!" << endl;
                return;
            }
        }
    }

    int search(const string &s) const
    {

        int index = Hash(s, size);

        int probe = 0;

        for (const auto &p : table[index])
        {
            probe++;
            if (p.first == s)
            {
                cout << "Element found at probe " << probe << "!" << endl;
                return probe;
            }
        }

        cout << "Element not found!" << endl;
        return 0;
    }
    double averageProbing(const vector<string> &selected_words) const {
        int total_probes = 0;
        for (const string &word : selected_words) {
            int probe = search(word);
            total_probes += probe;
        }

        double average_probe = static_cast<double>(total_probes) / selected_words.size();

        return average_probe;
    }


    void show()
    {
        for (int i = 0; i < size; i++)
        {
            cout << i << ": ";
            for (auto &p : table[i])
            {
                cout << p.first << " " << p.second << " ";
            }
            cout << endl;
        }
    }
};
int count_collisions(const vector<list<pair<string, int>>> &table)
{
    int total_collisions = 0;
    for (const auto &chain : table)
    {
        if (chain.size() > 1)
        {
            total_collisions += chain.size() - 1;
        }
    }
    return total_collisions;
}


int main()
{

    freopen("output.txt", "w", stdout);
    vector<string> generated_words = generate_unique_words(5000);
    // show_generated_words_with_index(generated_words);
    vector<string> selected_words = select_random_words(generated_words, 1000);
    show_generated_words_with_index(selected_words);
    HashTable hash_table(500, 5000);
    hash_table.insert(generated_words);
    hash_table.show();

    //cout<<hash_table.search(selected_words[5]);
    cout<<"Average Probing: "<<hash_table.averageProbing(selected_words)<<endl;
    hash_table.erase_all(selected_words);
    // hash_table.erase(selected_words[5]);
    cout<<hash_table.search(selected_words[5]);
    int total_collisions = count_collisions(hash_table.table);
    cout << "Total Collisions: " << total_collisions << endl;

    return 0;
}
