#ifndef SINGLETON_H
#define SINGLETON_H

template<class T>
class Singleton
{
protected:
    static T mSingleton;
public:
    inline static T& getInstance() { return mSingleton;}
};

#endif // SINGLETON_H
