#include <iostream>
#include <stdexcept>
#include <vector>

class Iterator;
class ConcreteAggregate;
/*
 * Aggregate
 * defines an interface for aggregates and it decouples your
 * client from the implementation of your collection of objects
 */
class Aggregate
{
public:
  virtual ~Aggregate() {}
  
  virtual Iterator *createIterator() = 0;
  // ...
};

/*
 * Concrete Aggregate
 * has a collection of objects and implements the method
 * that returns an Iterator for its collection
 *
 */
class ConcreteAggregate : public Aggregate
{
public:
  ConcreteAggregate( const unsigned int size )
  {
    list = new int[size]();
    count = size;
  }
  
  ~ConcreteAggregate()
  {
    delete[] list;
  }
  
  Iterator *createIterator();
  
  unsigned int size() const
  {
    return count;
  }
  
  int at( unsigned int index )
  {
    return list[ index ];
  }
  // ...

private:
  int *list;
  unsigned int count;
  // ...
};

/*
 * Iterator
 * provides the interface that all iterators must implement and
 * a set of methods for traversing over elements
 */
class Iterator
{
public:
  virtual ~Iterator() { /* ... */ }
  
  virtual void first() = 0;
  virtual void next() = 0;
  virtual bool isDone() const = 0;
  virtual int currentItem() const = 0;
  // ...
};

/*
 * Concrete Iterator
 * implements the interface and is responsible for managing
 * the current position of the iterator
 */
class ConcreteIterator : public Iterator
{
public:
  ConcreteIterator( ConcreteAggregate *l ) :
    list( l ), index( 0 ) {}
  
  ~ConcreteIterator() {}
  
  void first()
  {
    index = 0;
  }
  
  void next()
  {
    index++;
  }
  
  bool isDone() const
  {
    return ( index >= list->size() );
  }
  
  int currentItem() const
  {
    if ( isDone() )
    {
      return -1;
    }
    return list->at(index);
  }
  // ...

private:
  ConcreteAggregate *list;
  unsigned int index;
  // ...
};

Iterator *ConcreteAggregate::createIterator()
{
  return new ConcreteIterator( this );
}
void testCreateIterator() {
    unsigned int size = 5;
    ConcreteAggregate list(size);
    Iterator* it = list.createIterator();
    if (it != nullptr) {
        std::cout << "Test 1 passed: Iterator created successfully." << std::endl;
    } else {
        std::cout << "Test 1 failed: Iterator creation failed." << std::endl;
    }
    delete it;
}

// Тест 2: Проверка методов first и isDone для ConcreteIterator
void testIteratorFirstAndIsDone() {
    unsigned int size = 5;
    ConcreteAggregate list(size);
    Iterator* it = list.createIterator();
    it->first();
    if (!it->isDone()) {
        std::cout << "Test 2 passed: first() and isDone() methods work correctly." << std::endl;
    } else {
        std::cout << "Test 2 failed: first() or isDone() method is incorrect." << std::endl;
    }
    delete it;
}

// Тест 3: Проверка методов next и currentItem для ConcreteIterator
void testIteratorNextAndCurrentItem() {
    unsigned int size = 5;
    ConcreteAggregate list(size);
    Iterator* it = list.createIterator();
    it->first();
    for (unsigned int i = 0; i < size; ++i) {
        if (it->currentItem() == list.at(i)) {
            it->next();
        } else {
            std::cout << "Test 3 failed: next() or currentItem() method is incorrect." << std::endl;
            delete it;
            return;
        }
    }
    if (it->isDone()) {
        std::cout << "Test 3 passed: next() and currentItem() methods work correctly." << std::endl;
    } else {
        std::cout << "Test 3 failed: next() or currentItem() method is incorrect." << std::endl;
    }
    delete it;
}

int main() {
    testCreateIterator();
    testIteratorFirstAndIsDone();
    testIteratorNextAndCurrentItem();
    return 0;
}
