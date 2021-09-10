#include "Hashtable.h"

#include <iostream>
#include <math.h>
#include <string>
#include <utility>

// constructor, passing in two parameters, debug mode or not, which probing
Hashtable::Hashtable(bool debug, int probing) {
    _debug = debug, _probing = probing;
    _size = 11;
    _arr = new std::pair<std::string, int>[_size];
    _table = new bool[_size];
    for (int i = 0; i < _size; i++) {
        _table[i] = false;
    }

    _occupied = 0;
    _resizeCount = 0;

    // initialize r
    if (_debug) {
        _r[0] = 983132572;
        _r[1] = 62337998;
        _r[2] = 552714139;
        _r[3] = 984953261;
        _r[4] = 261934300;
    } else {
        for (int i = 0; i < 5; i++) {
            _r[i] = rand() % _size;
        }
    }
}

// deconstructor
Hashtable::~Hashtable() {
    delete[] _arr;
    delete[] _table;
}

// add function
void Hashtable::add(std::string k) {

    // determine if loading factor is bigger than 0.5
    if (((double)_occupied) / _size >= 0.5) {
        resize();
    }

    int hash_value = hash(k);
    int index = hash_value;
    for (int i = 0; i < _size; i++) {
        // if this index is empty, insert a new pair
        if (!_table[index]) {
            _arr[index] = std::make_pair(k, 1);
            _table[index] = true;
            _occupied++;
            return;
        }
        // if the string in this index is the same as k, imcrement its value
        else if (_arr[index].first == k) {
            _arr[index].second++;
            return;
        }
        // linear probing
        if (_probing == 0) {
            index++;
            index %= _size;

        }
        // quadratic probing
        else if (_probing == 1) {
            index = hash_value + pow(i + 1, 2);
            index %= _size;

        }
        // double hasing
        else {
            index = hash_value + (i + 1) * doubleHash(k);
            index %= _size;
        }
    }
}

// count function return the value associated with k, return 0 if not found
int Hashtable::count(std::string k) {

    int hash_value = hash(k);
    int index = hash_value;
    for (int i = 0; i < _size; i++) {
        if (!_table[index]) {
            return 0;
        } else if (_arr[index].first == k) {
            return _arr[index].second;
        }
        // linear probing
        if (_probing == 0) {
            index++;
            index %= _size;

        }
        // quadratic probing
        else if (_probing == 1) {
            index = hash_value + pow(i + 1, 2);
            index %= _size;

        }
        // double hasing
        else {
            index = hash_value + (i + 1) * doubleHash(k);
            index %= _size;
        }
    }

    return 0;
}

// output all key value pair to the give stream
void Hashtable::reportAll(std::ostream& ofile) const {

    for (int i = 0; i < _size; i++) {
        if (_table[i]) {
            ofile << i << " " << _arr[i].first << " " << _arr[i].second << std::endl;
        }
    }
}

// hash function
int Hashtable::hash(std::string k) const {
    int num = (k.length() - 1) / 6 + 1;
    int pos = k.length() - 1;
    int values[num];
    for (int i = num - 1; i >= 0; i--) {
        int temp = 0;
        for (int j = 0; j < 6; j++) {
            if (pos >= 0)
                temp = temp + pow(26, j) * (k[pos] - 'a');
            pos--;
        }
        values[i] = temp;
    }
    long long int val = 0;
    int m = 4;
    for (int i = num - 1; i >= 0; i--) {
        val += (values[i] * _r[m]);
        m--;
    }
    return val % _size;
}

// double hashing
int Hashtable::doubleHash(std::string k) const {
    int num = (k.length() - 1) / 6 + 1;
    int pos = k.length() - 1;
    int values[num];
    for (int i = num - 1; i >= 0; i--) {
        int temp = 0;
        for (int j = 0; j < 6; j++) {
            if (pos >= 0)
                temp = temp + pow(26, j) * (k[pos] - 'a');
            pos--;
        }
        values[i] = temp;
    }
    int val = 0;
    for (int j = 0; j < num; j++) {
        val += values[j];
    }
    return _p[_resizeCount] - (val % _p[_resizeCount]);
}

// resize helper function, call when loading factor is above 0.5
void Hashtable::resize() {

    _resizeCount++;
    _occupied = 0;
    int temp_size = _size;
    _size = _sizeList[_resizeCount];
    std::pair<std::string, int>* temp_arr = _arr;
    bool* temp_table = _table;
    _arr = new std::pair<std::string, int>[_size];
    _table = new bool[_size];
    for (int i = 0; i < _size; i++) {
        _table[i] = false;
    }

    // re-add all existing key-value pairs
    for (int i = 0; i < temp_size; i++) {
        if (temp_table[i]) {
            int count = temp_arr[i].second;
            while (count > 0) {
                add(temp_arr[i].first);
                count--;
            }
        }
    }

    if (!_debug) {
        for (int i = 0; i < 5; i++) {
            _r[i] = rand() % _size;
        }
    }

    delete[] temp_arr;
    delete[] temp_table;
}
