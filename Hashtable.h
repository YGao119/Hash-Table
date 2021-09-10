#include <fstream>
#include <iostream>
#include <string>
#include <utility>

class Hashtable {

public:
    Hashtable(bool debug, int probing);
    ~Hashtable();
    void add(std::string k);  // If k is already in the HashTable, then increment its value. If it is new, add it to the
                              // HashTable with a value of 1
    int count(std::string k);             // Returns the int associated with k, or 0 if k is not in the Hashtable
    void reportAll(std::ostream&) const;  // output, to the given stream, every (key,value) pair

private:
    void resize();                        // helper function, call when the loading factor is above 0.5
    int hash(std::string k) const;        // hash function, return index
    int doubleHash(std::string k) const;  // double hashing function

    std::pair<std::string, int>* _arr;
    bool* _table;
    long long int _r[5];
    int _resizeCount;
    int _sizeList[28]
            = {11,       23,       47,       97,        197,       397,       797,       1597,      3203,    6421,
               12853,    25717,    51437,    102877,    205759,    411527,    823117,    1646237,   3292489, 6584983,
               13169977, 26339969, 52679969, 105359969, 210719881, 421439783, 842879579, 1685759167};
    int _p[28] = {7,        19,       43,       89,        193,       389,       787,       1583,      3191,    6397,
                  12841,    25703,    51431,    102871,    205721,    411503,    823051,    1646221,   3292463, 6584957,
                  13169963, 26339921, 52679927, 105359939, 210719881, 421439749, 842879563, 1685759113};
    int _size;
    int _occupied;
    int _probing;
    bool _debug;
};
