template <typename Object>
class ArrayVector {
private:
    int capacity;   // length of array
    int sz;         // number of elements in vector
    Object* a;      // array storing the elements
protected:
    void overflow() {               // handle overflow by resizing
        capacity *= 2;              // double capacity
        Object* b = new Object[capacity];
        for (int i = 0; i < sz; i++) b[i] = a[i];// copy contents to new array
        delete [] a;                // discard old array
        a = b;                      // make b the new array
    }
public:
    ArrayVector(int initCap = 16) {     // constructor
        capacity = initCap;
        sz = 0;
        a = new Object[capacity];
    }
    int size() const{ return sz; }              // number of elements
    bool isEmpty() const{ return size() == 0; } // is vector empty?
    Object& elemAtRank(int r){ return a[r]; }   // access element at rank r
    void replaceAtRank(int r, const Object& e){ // replace element at given rank
        a[r] = e; }
    void removeAtRank(int r){                   // remove element at given rank
        for (int i = r; i < sz-1; i++) a[i] = a[i+1];// shift elements down
        sz--; }
    void insertAtRank(int r, const Object& e) { // insert element at given rank
        if (sz == capacity) overflow(); // handle overflow
        for (int i = sz-1; i >= r; i--) a[i+1] = a[i]; // shift elements up
        a[r] = e;
        sz++;   }
    // ... (housekeeping functions omitted)
};
