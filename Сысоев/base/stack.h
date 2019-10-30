#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
  T *pMem;
  int size;
  int top;
public:
  TStack(int _size = MaxStackSize)
  {
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
      throw size;
    pMem = new T[size];
  }
 
  bool isEmpty()
  {
	  if (top < 0)
		  return true;
	  else
		  return false;
  
  }
  T pop()
  {
	  if (!isEmpty())
		  return pMem[top--];
	  else
		  throw 1;
  }

  T Top()
  {
	  if (!isEmpty())
		  return pMem[top];
	  else
		  throw 1;
  }

  void push(T val)
  {
	  if (top + 1 < size)
		  pMem[++top] = val;
	  else
		  throw 1;
  }

  ~TStack()
  {
    delete [] pMem;
  }
};

#endif
