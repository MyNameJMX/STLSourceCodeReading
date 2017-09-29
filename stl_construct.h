//第一版本的构造函数
//palacement new 预先已经有一块内存，只构造对象，将对象创建在这块地址已知的内存上
template <class _T1, class _T2>
inline void _Construct(_T1* __p, const _T2& __value) {
  new ((void*) __p) _T1(__value);
}
//第二版本的构造函数
template <class _T1>
inline void _Construct(_T1* __p) {
  new ((void*) __p) _T1();
----------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------
//第一版本接受一个指针，准备将该指针所指之物析构掉  
template <class _Tp> 
inline void _Destroy(_Tp* __pointer) {
  __pointer->~_Tp();
}

//此处__false_type以及__true_type是指是否有non-trivial destructor（自定义的析构函数）
//__false_type有，__true_type没有

//第二版本接受first与last两个迭代器，准备将[first,last)范围内所有对象析构掉
template <class _ForwardIterator>  
void  
__destroy_aux(_ForwardIterator __first, _ForwardIterator __last, __false_type)
{
  for ( ; __first != __last; ++__first)
    destroy(&*__first);
}

//若有默认的析构函数 不需要处理 之后会自行调用析构函数
template <class _ForwardIterator> 
inline void __destroy_aux(_ForwardIterator, _ForwardIterator, __true_type) {}

//判断_Tp*是否has_trivial_destructor 决定调用那个版本的__destory_aux
template <class _ForwardIterator, class _Tp>
inline void 
__destroy(_ForwardIterator __first, _ForwardIterator __last, _Tp*)
{
  typedef typename __type_traits<_Tp>::has_trivial_destructor
          _Trivial_destructor;
  __destroy_aux(__first, __last, _Trivial_destructor());
}

template <class _ForwardIterator>
inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last) {
  __destroy(__first, __last, __VALUE_TYPE(__first));
}

