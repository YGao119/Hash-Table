# Programming Assignment 6

## Hash Table

    Hashtable<string,int> data structure with probing for collision resolution

### Functions

    add (string k): If k is already in the HashTable, then increment its value. If it is new, add it to the HashTable with a value of 1.
    count (string k): Returns the int associated with k, or 0 if k is not in the Hashtable.
    reportAll (ostream &) const : output, to the given stream, every (key,value) pair, in the order they appear in the hashtable; on each line, output the key, followed by a space, followed by the value, and then a newline.

### Analyze the Hashtable 

#### Which size of input cases did you use?
    The size of input cases: 31945 words
#### Did you use AVL Trees or the STL map?
    I use AVL Trees 
#### For each of the 4 approaches (linear probing, quadratic probing, double hashing, AVL Trees), report how long each of your input cases took. How long did it take per operation?
    linear probing:     each of my input cases takes 0.0214987 s  |  it takes 7.4715918e-7 
    quadratic probing:  each of my input cases takes 0.021844 s   |  it takes 7.03408984e-7 
    double hashing:     each of my input cases takes 0.0244632 s  |  it takes 8.31917358e-7
    AVL Trees:          each of my input cases takes 0.0236764 s  |  it takes 7.4715918e-7 
#### Explain why you think the results turned out the way they did, and whether you were surprised by them.
    
    Since Hash table has a constant average runtime, no matter the input case is small or large, Hash table will have an overall better performance than AVL Tree which has a theta(log(n)) worst case runtime and average runtime. However, when using double hashing to handle collision, it takes slightly more time compared to other probings and AVL Tree. The reanson could be that my double hashing function is not efficient enough and my add function calls doubles hashing function multiple times. I have tried to only call double hashing function once at the beginning of my add function, but doing so makes the runtime even worse, which I am very suprised of. 
