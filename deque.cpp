/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque():num(0),L(-1){}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T const& newItem)
{
    /**
     * @todo Your code here!
     */
     if (L== -1 ) {
       L++;
     }
     num++;
     data.push_back(newItem);
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes.
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    /**
     * @todo Your code here! You will need to replace the following line.
     */

    //assume nonempty

    //return T();
    //resizes
    T removed = peekL();
    L++;
    num--;
    if (num <= L ) {
      for (int i = 0; i < num ; i++) {
        data[i] = data[i+L];
      }
      L = 0; //reinitialize l
      data.resize(num);
    }
    return removed;
}
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    /**
     * @todo Your code here! You will need to replace the following line.
     */
     //assume nonempty
    //return T();
    T removed = peekR();
    data.pop_back();
    num--;
    if (num <= L && L != 0) {
      for (int i = 0; i < num ; i++) {
        data[i] = data[i+L];
      }
      data.resize(num);
      L = 0; //reinitialize l
    }
    return removed;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    /**
     * @todo Your code here! You will need to replace the following line.
     */

     //called when it is non-empty

    //return T();
    return data[L];
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    /**
     * @todo Your code here! You will need to replace the following line.
     */

     //assume non empty
    //return T();
    return data[num-1];
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    /**
     * @todo Your code here! You will need to replace the following line.
     */

    return (num == 0);
}