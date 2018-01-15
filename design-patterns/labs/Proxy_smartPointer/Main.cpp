// Please, implement a proxy class for MyClass objects which is called UniquePointer. The
// class contains a pointer to an object of type MyClass. The
// UniquePointer object behaves like a pointer i.e. -> provides access
// to the object but has additional features:
// - it contains print method which provides information to which
//   object is it pointing
// - only one object of type UniquePointer can store a pointer to a
//   given object of type MyClass. This means that when assignemnt
//   ptr2 = ptr1
//   is done, the pointer is stored in object ptr2 and is
//   deleted from object ptr1
// - when object of type UniquePointer is pointing to an object and
//   UniquePointer is deleted (e.g. goes out of scope) or is assigned
//   different value the object it was pointing to is deleted, so that
//   no memory leaks are possible

// Please, make sure that there are no problems with memory after
// implementing UniquePointer.

// Comments in the code show what is the output from the given line

#include"UniquePointer.h"
#include"MyClass.h"

int main ()
{
  UniquePointer ptr1 (new MyClass ("dynamic1"));
  ptr1.print();			// This is a pointer to dynamic1
  ptr1->print();		// This is dynamic1

  UniquePointer ptr2 = ptr1;
  ptr1.print();			// This object does not point to anything
  ptr2.print();			// This is a pointer to dynamic1

  ptr2 = new MyClass ("dynamic2");
  ptr2 = ptr2;
  ptr2.print();			// This is a pointer to dynamic2

  ptr1 = ptr2;			
  ptr1.print();			// This is a pointer to dynamic2

  ptr1->print();		// This is dynamic2

  return 0;
}
/*
Constructing object dynamic1
This is pointer to dynamic1
This is dynamic1
This is object  does not point to anything
This is pointer to dynamic1
Constructing object dynamic2
Destroying object dynamic1
This is pointer to dynamic2
This is pointer to dynamic2
This is dynamic2
Destroying object dynamic2
*/
