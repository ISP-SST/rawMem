/* --------------------------------------------------------
   Template function to create C-style multidimensional arrays with raw pointers.
   The memory block is allocated at once to ensure that it is contiguous.
   
   These routines are based on some old C routines by M. van Noort, but 
   in this case using templates allows not having to write them for 
   every single variable type.
   
   Coded by J. de la Cruz Rodriguez (ISP-SU 2019)
 */
#ifndef RMEM_HPP
#define RMEM_HPP

#include <cstdlib>

namespace rmem{

  // ****************************************************************** //
  
  template<typename T> T* rarray(long const& x0, long const& x1)
    {
      return new T [x1-x0+1]() - x0;
    }

  template<typename T> void del_rarray(T *&v, long const& x0)
    {
      delete [] (v+x0);
      v = NULL;
    }
  
  // ****************************************************************** //

  template<typename T> T** rarray(long const& x0l, long const &x0h, long const& x1l, long const& x1h)
    {
      const long nx0 = x0h-x0l+1, nx1=x1h-x1l+1;
      T **d = new T* [nx0] - x0l;
      d[x0l] = new T [nx0*nx1] - x1l;
      for(long x0=x0l+1;x0<=x0h; ++x0) d[x0] = d[x0-1] + nx1;
      return d;
    }

  template<typename T> void del_rarray(T **&v, long const &x0l, long const &x1l)
    {
      delete [] (v[x0l]+x1l);
      delete [] (v+x0l);
      v = NULL;
    }

  // ****************************************************************** //

  template<typename T> T*** rarray(long const& x1l, long const &x1h, long const& x2l, long const& x2h, long const& x3l, long const& x3h)
    {
      const long nx1=x1h-x1l+1,nx2=x2h-x2l+1,nx3=x3h-x3l+1;
      T ***p=new T** [nx1] - x1l;
      p[x1l]=new T* [nx1*nx2] - x2l;
      p[x1l][x2l]=new T [nx1*nx2*nx3]() - x3l;
      for(long x2=x2l+1;x2<=x2h;++x2) p[x1l][x2]=p[x1l][x2-1]+nx3;
      for(long x1=x1l+1;x1<=x1h;++x1){
	p[x1]=p[x1-1]+nx2;
	p[x1][x2l]=p[x1-1][x2l]+nx2*nx3;
	for(long x2=x2l+1;x2<=x2h;++x2) p[x1][x2]=p[x1][x2-1]+nx3;
      }
      return p;
    }

  template <typename T> void del_rarray(T ***&p, long const& x1l, long const& x2l, long const& x3l)
    {
      delete[] (p[x1l][x2l]+x3l);
      delete[] (p[x1l]+x2l);
      delete[] (p+x1l);
      p = NULL;
    }
  
  // ****************************************************************** //

  template <typename T> T**** rarray(long const& x1l,long const& x1h,long const& x2l,long const& x2h,long const& x3l,long const& x3h,long const& x4l,long const& x4h)
    {
      const long nx1=x1h-x1l+1,nx2=x2h-x2l+1,nx3=x3h-x3l+1,nx4=x4h-x4l+1;
      double ****p = new T*** [nx1] - x1l;
      p[x1l]=new T** [nx1*nx2] - x2l;
      p[x1l][x2l]=new T* [nx1*nx2*nx3] - x3l;
      p[x1l][x2l][x3l]=new T [nx1*nx2*nx3*nx4] - x4l;
      for(long x3=x3l+1;x3<=x3h;++x3) p[x1l][x2l][x3]=p[x1l][x2l][x3-1]+nx4;
      for(long x2=x2l+1;x2<=x2h;++x2){
	p[x1l][x2]=p[x1l][x2-1]+nx3;
	p[x1l][x2][x3l]=p[x1l][x2-1][x3l]+nx3*nx4;
	for(long x3=x3l+1;x3<=x3h;++x3) p[x1l][x2][x3]=p[x1l][x2][x3-1]+nx4;
      }
      for(long x1=x1l+1;x1<=x1h;++x1) {
	p[x1]=p[x1-1]+nx2;
	p[x1][x2l]=p[x1-1][x2l]+nx2*nx3;
	p[x1][x2l][x3l]=p[x1-1][x2l][x3l]+nx2*nx3*nx4;
	for(long x3=x3l+1;x3<=x3h;++x3) p[x1][x2l][x3]=p[x1][x2l][x3-1]+nx4;
	for(long x2=x2l+1;x2<=x2h;++x2){
	  p[x1][x2]=p[x1][x2-1]+nx3;
	  p[x1][x2][x3l]=p[x1][x2-1][x3l]+nx3*nx4;
	  for(long x3=x3l+1;x3<=x3h;++x3) p[x1][x2][x3]=p[x1][x2][x3-1]+nx4;
	}
      }
      return p;
    }
  

  template<typename T> void del_rarray(T ****&p,  long const& x1l, long const& x2l, long const& x3l, long const& x4l)
    {
      delete[] (p[x1l][x2l][x3l]+x4l);
      delete[] (p[x1l][x2l]+x3l);
      delete[] (p[x1l]+x2l);
      delete[] (p+x1l);
      p = NULL;
    }
  
  
  // ****************************************************************** //

  template<typename T> T***** rarray(long const& x1l,long const& x1h,long const& x2l,long const& x2h,long const& x3l,long const& x3h,long const& x4l,long const& x4h,long const& x5l,long const& x5h)
    {
      const long nx1=x1h-x1l+1,nx2=x2h-x2l+1,nx3=x3h-x3l+1,nx4=x4h-x4l+1,nx5=x5h-x5l+1;
      T *****p=new T**** [nx1] - x1l;
      p[x1l]=new T*** [nx1*nx2] - x2l;
      p[x1l][x2l]=new T** [nx1*nx2*nx3] - x3l;
      p[x1l][x2l][x3l]=new T* [nx1*nx2*nx3*nx4] - x4l;
      p[x1l][x2l][x3l][x4l]=new T [nx1*nx2*nx3*nx4*nx5]() - x5l;
      for(long x4=x4l+1;x4<=x4h;++x4) p[x1l][x2l][x3l][x4]=p[x1l][x2l][x3l][x4-1]+nx5;
      for(long x3=x3l+1;x3<=x3h;++x3){
	p[x1l][x2l][x3]=p[x1l][x2l][x3-1]+nx4;    
	p[x1l][x2l][x3][x4l]=p[x1l][x2l][x3-1][x4l]+nx4*nx5;
	for(long x4=x4l+1;x4<=x4h;++x4) p[x1l][x2l][x3][x4]=p[x1l][x2l][x3][x4-1]+nx5;
      }
      for(long x2=x2l+1;x2<=x2h;++x2){
	p[x1l][x2]=p[x1l][x2-1]+nx3;
	p[x1l][x2][x3l]=p[x1l][x2-1][x3l]+nx3*nx4;
	p[x1l][x2][x3l][x4l]=p[x1l][x2-1][x3l][x4l]+nx3*nx4*nx5;
	for(long x4=x4l+1;x4<=x4h;++x4) p[x1l][x2][x3l][x4]=p[x1l][x2][x3l][x4-1]+nx5;
	for(long x3=x3l+1;x3<=x3h;++x3){
	  p[x1l][x2][x3]=p[x1l][x2][x3-1]+nx4;
	  p[x1l][x2][x3][x4l]=p[x1l][x2][x3-1][x4l]+nx4*nx5;
	  for(long x4=x4l+1;x4<=x4h;++x4) p[x1l][x2][x3][x4]=p[x1l][x2][x3][x4-1]+nx5;
	}
      }	
      for(long x1=x1l+1;x1<=x1h;++x1) {
	p[x1]=p[x1-1]+nx2;
	p[x1][x2l]=p[x1-1][x2l]+nx2*nx3;
	p[x1][x2l][x3l]=p[x1-1][x2l][x3l]+nx2*nx3*nx4;
	p[x1][x2l][x3l][x4l]=p[x1-1][x2l][x3l][x4l]+nx2*nx3*nx4*nx5;
	for(long x4=x4l+1;x4<=x4h;++x4) p[x1][x2l][x3l][x4]=p[x1][x2l][x3l][x4-1]+nx5;
	for(long x3=x3l+1;x3<=x3h;++x3){
	  p[x1][x2l][x3]=p[x1][x2l][x3-1]+nx4;
	  p[x1][x2l][x3][x4l]=p[x1][x2l][x3-1][x4l]+nx4*nx5;
	  for(long x4=x4l+1;x4<=x4h;++x4) p[x1][x2l][x3][x4]=p[x1][x2l][x3][x4-1]+nx5;
	}
	for(long x2=x2l+1;x2<=x2h;++x2){
	  p[x1][x2]=p[x1][x2-1]+nx3;
	  p[x1][x2][x3l]=p[x1][x2-1][x3l]+nx3*nx4;
	  p[x1][x2][x3l][x4l]=p[x1][x2-1][x3l][x4l]+nx3*nx4*nx5;
	  for(long x4=x4l+1;x4<=x4h;++x4) p[x1][x2][x3l][x4]=p[x1][x2][x3l][x4-1]+nx5;
	  for(long x3=x3l+1;x3<=x3h;++x3){
	    p[x1][x2][x3]=p[x1][x2][x3-1]+nx4;
	    p[x1][x2][x3][x4l]=p[x1][x2][x3-1][x4l]+nx4*nx5;
	    for(long x4=x4l+1;x4<=x4h;++x4) p[x1][x2][x3][x4]=p[x1][x2][x3][x4-1]+nx5;
	  }
	}
      }
      return p;
    }
  
  template<typename T> void del_rarray(T *****&p, long const& x1l,long const& x2l,long const& x3l,long const& x4l,long const& x5l)
    {
      delete[] (p[x1l][x2l][x3l][x4l]+x5l);
      delete[] (p[x1l][x2l][x3l]+x4l);
      delete[] (p[x1l][x2l]+x3l);
      delete[] (p[x1l]+x2l);
      delete[] (p+x1l);
      p = NULL;
    }
  
  // ****************************************************************** //
  
  
  template<typename T> T ******rarray(long const& x1l,long const& x1h,long const& x2l,long const& x2h,long const& x3l,long const& x3h,long const& x4l,long const& x4h,long const& x5l,long const& x5h,long const& x6l,long const& x6h)
    {
      const long nx1=x1h-x1l+1,nx2=x2h-x2l+1,nx3=x3h-x3l+1,nx4=x4h-x4l+1,nx5=x5h-x5l+1,nx6=x6h-x6l+1;
      T ******p;
      p=new T***** [nx1] - x1l;
      p[x1l]=new T**** [nx1*nx2] - x2l;
      p[x1l][x2l]=new T*** [nx1*nx2*nx3] - x3l;
      p[x1l][x2l][x3l]=new T** [nx1*nx2*nx3*nx4] - x4l;
      p[x1l][x2l][x3l][x4l]=new T* [nx1*nx2*nx3*nx4*nx5] - x5l;
      p[x1l][x2l][x3l][x4l][x5l]=new T [nx1*nx2*nx3*nx4*nx5*nx6]() - x6l;
      for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2l][x3l][x4l][x5]=p[x1l][x2l][x3l][x4l][x5-1]+nx6;
      for(long x4=x4l+1;x4<=x4h;++x4){
	p[x1l][x2l][x3l][x4]=p[x1l][x2l][x3l][x4-1]+nx5;    
	p[x1l][x2l][x3l][x4][x5l]=p[x1l][x2l][x3l][x4-1][x5l]+nx5*nx6;
	for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2l][x3l][x4][x5]=p[x1l][x2l][x3l][x4][x5-1]+nx6;
      }
      for(long x3=x3l+1;x3<=x3h;++x3){
	p[x1l][x2l][x3]=p[x1l][x2l][x3-1]+nx4;
	p[x1l][x2l][x3][x4l]=p[x1l][x2l][x3-1][x4l]+nx4*nx5;
	p[x1l][x2l][x3][x4l][x5l]=p[x1l][x2l][x3-1][x4l][x5l]+nx4*nx5*nx6;
	for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2l][x3][x4l][x5]=p[x1l][x2l][x3][x4l][x5-1]+nx6;
	for(long x4=x4l+1;x4<=x4h;++x4){
	  p[x1l][x2l][x3][x4]=p[x1l][x2l][x3][x4-1]+nx5;    
	  p[x1l][x2l][x3][x4][x5l]=p[x1l][x2l][x3][x4-1][x5l]+nx5*nx6;
	  for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2l][x3][x4][x5]=p[x1l][x2l][x3][x4][x5-1]+nx6;
	}
      }
      for(long x2=x2l+1;x2<=x2h;++x2){
	p[x1l][x2]=p[x1l][x2-1]+nx3;
	p[x1l][x2][x3l]=p[x1l][x2-1][x3l]+nx3*nx4;
	p[x1l][x2][x3l][x4l]=p[x1l][x2-1][x3l][x4l]+nx3*nx4*nx5;
	p[x1l][x2][x3l][x4l][x5l]=p[x1l][x2-1][x3l][x4l][x5l]+nx3*nx4*nx5*nx6;
	for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2][x3l][x4l][x5]=p[x1l][x2][x3l][x4l][x5-1]+nx6;
	for(long x4=x4l+1;x4<=x4h;++x4){
	  p[x1l][x2][x3l][x4]=p[x1l][x2][x3l][x4-1]+nx5;    
	  p[x1l][x2][x3l][x4][x5l]=p[x1l][x2][x3l][x4-1][x5l]+nx5*nx6;
	  for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2][x3l][x4][x5]=p[x1l][x2][x3l][x4][x5-1]+nx6;
	}
	for(long x3=x3l+1;x3<=x3h;++x3){
	  p[x1l][x2][x3]=p[x1l][x2][x3-1]+nx4;
	  p[x1l][x2][x3][x4l]=p[x1l][x2][x3-1][x4l]+nx4*nx5;
	  p[x1l][x2][x3][x4l][x5l]=p[x1l][x2][x3-1][x4l][x5l]+nx4*nx5*nx6;
	  for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2][x3][x4l][x5]=p[x1l][x2][x3][x4l][x5-1]+nx6;
	  for(long x4=x4l+1;x4<=x4h;++x4){
	    p[x1l][x2][x3][x4]=p[x1l][x2][x3][x4-1]+nx5;    
	    p[x1l][x2][x3][x4][x5l]=p[x1l][x2][x3][x4-1][x5l]+nx5*nx6;
	    for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2][x3][x4][x5]=p[x1l][x2][x3][x4][x5-1]+nx6;
	  }
	}
      }
      for(long x1=x1l+1;x1<=x1h;++x1){
	p[x1]=p[x1-1]+nx2;
	p[x1][x2l]=p[x1-1][x2l]+nx2*nx3;
	p[x1][x2l][x3l]=p[x1-1][x2l][x3l]+nx2*nx3*nx4;
	p[x1][x2l][x3l][x4l]=p[x1-1][x2l][x3l][x4l]+nx2*nx3*nx4*nx5;
	p[x1][x2l][x3l][x4l][x5l]=p[x1-1][x2l][x3l][x4l][x5l]+nx2*nx3*nx4*nx5*nx6;
	for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2l][x3l][x4l][x5]=p[x1][x2l][x3l][x4l][x5-1]+nx6;
	for(long x4=x4l+1;x4<=x4h;++x4){
	  p[x1][x2l][x3l][x4]=p[x1][x2l][x3l][x4-1]+nx5;    
	  p[x1][x2l][x3l][x4][x5l]=p[x1][x2l][x3l][x4-1][x5l]+nx5*nx6;
	  for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2l][x3l][x4][x5]=p[x1][x2l][x3l][x4][x5-1]+nx6;
	}
	for(long x3=x3l+1;x3<=x3h;++x3){
	  p[x1][x2l][x3]=p[x1][x2l][x3-1]+nx4;
	  p[x1][x2l][x3][x4l]=p[x1][x2l][x3-1][x4l]+nx4*nx5;
	  p[x1][x2l][x3][x4l][x5l]=p[x1][x2l][x3-1][x4l][x5l]+nx4*nx5*nx6;
	  for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2l][x3][x4l][x5]=p[x1][x2l][x3][x4l][x5-1]+nx6;
	  for(long x4=x4l+1;x4<=x4h;++x4){
	    p[x1][x2l][x3][x4]=p[x1][x2l][x3][x4-1]+nx5;    
	    p[x1][x2l][x3][x4][x5l]=p[x1][x2l][x3][x4-1][x5l]+nx5*nx6;
	    for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2l][x3][x4][x5]=p[x1][x2l][x3][x4][x5-1]+nx6;
	  }
	}
	for(long x2=x2l+1;x2<=x2h;++x2){
	  p[x1][x2]=p[x1][x2-1]+nx3;
	  p[x1][x2][x3l]=p[x1][x2-1][x3l]+nx3*nx4;
	  p[x1][x2][x3l][x4l]=p[x1][x2-1][x3l][x4l]+nx3*nx4*nx5;
	  p[x1][x2][x3l][x4l][x5l]=p[x1][x2-1][x3l][x4l][x5l]+nx3*nx4*nx5*nx6;
	  for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2][x3l][x4l][x5]=p[x1][x2][x3l][x4l][x5-1]+nx6;
	  for(long x4=x4l+1;x4<=x4h;++x4){
	    p[x1][x2][x3l][x4]=p[x1][x2][x3l][x4-1]+nx5;    
	    p[x1][x2][x3l][x4][x5l]=p[x1][x2][x3l][x4-1][x5l]+nx5*nx6;
	    for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2][x3l][x4][x5]=p[x1][x2][x3l][x4][x5-1]+nx6;
	  }
	  for(long x3=x3l+1;x3<=x3h;++x3){
	    p[x1][x2][x3]=p[x1][x2][x3-1]+nx4;
	    p[x1][x2][x3][x4l]=p[x1][x2][x3-1][x4l]+nx4*nx5;
	    p[x1][x2][x3][x4l][x5l]=p[x1][x2][x3-1][x4l][x5l]+nx4*nx5*nx6;
	    for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2][x3][x4l][x5]=p[x1][x2][x3][x4l][x5-1]+nx6;
	    for(long x4=x4l+1;x4<=x4h;++x4){
	      p[x1][x2][x3][x4]=p[x1][x2][x3][x4-1]+nx5;    
	      p[x1][x2][x3][x4][x5l]=p[x1][x2][x3][x4-1][x5l]+nx5*nx6;
	      for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2][x3][x4][x5]=p[x1][x2][x3][x4][x5-1]+nx6;
	    }
	  }
	}
      }
      return p;
    }
  
  template<typename T> void del_rarray(T ******&p,long const& x1l,long const& x2l,long const& x3l,long const& x4l,long const& x5l,long const& x6l)
  {
    delete[] (p[x1l][x2l][x3l][x4l][x5l]+x6l);
    delete[] (p[x1l][x2l][x3l][x4l]+x5l);
    delete[] (p[x1l][x2l][x3l]+x4l);
    delete[] (p[x1l][x2l]+x3l);
    delete[] (p[x1l]+x2l);
    delete[] (p+x1l);
    p = NULL;
  }
  
  // ****************************************************************** //

  template<typename T> T** rmap(T *v, long const& x0l, long const &x0h, long const& x1l, long const& x1h)
  {
    const long nx0 = x0h-x0l+1, nx1=x1h-x1l+1;
    T **d = new T* [nx0] - x0l;
    d[x0l] = v - x1l;
    for(long x0=x0l+1;x0<=x0h; ++x0) d[x0] = d[x0-1] + nx1;
    return d;
  }
  
  template<typename T> void del_rmap(T **&v, long const &x0l, long const &x1l)
  {
    //delete [] (v[x0l]+x1l);
    delete [] (v+x0l);
    v = NULL;
  }

  // ***************************************************************** // 

  template<typename T> T*** rmap(T *v, long const& x1l, long const &x1h, long const& x2l, long const& x2h, long const& x3l, long const& x3h)
    {
      const long nx1=x1h-x1l+1,nx2=x2h-x2l+1,nx3=x3h-x3l+1;
      T ***p=new T** [nx1] - x1l;
      p[x1l]=new T* [nx1*nx2] - x2l;
      p[x1l][x2l]= v - x3l;
      for(long x2=x2l+1;x2<=x2h;++x2) p[x1l][x2]=p[x1l][x2-1]+nx3;
      for(long x1=x1l+1;x1<=x1h;++x1){
	p[x1]=p[x1-1]+nx2;
	p[x1][x2l]=p[x1-1][x2l]+nx2*nx3;
	for(long x2=x2l+1;x2<=x2h;++x2) p[x1][x2]=p[x1][x2-1]+nx3;
      }
      return p;
    }

  template <typename T> void del_rmap(T ***&p, long const& x1l, long const& x2l, long const& x3l)
    {
      //delete[] (p[x1l][x2l]+x3l);
      delete[] (p[x1l]+x2l);
      delete[] (p+x1l);
      p = NULL;
    }

  // ***************************************************************** // 

  template <typename T> T**** rmap(T *v, long const& x1l,long const& x1h,long const& x2l,long const& x2h,long const& x3l,long const& x3h,long const& x4l,long const& x4h)
    {
      const long nx1=x1h-x1l+1,nx2=x2h-x2l+1,nx3=x3h-x3l+1,nx4=x4h-x4l+1;
      double ****p = new T*** [nx1] - x1l;
      p[x1l]=new T** [nx1*nx2] - x2l;
      p[x1l][x2l]=new T* [nx1*nx2*nx3] - x3l;
      p[x1l][x2l][x3l] = v - x4l;
      for(long x3=x3l+1;x3<=x3h;++x3) p[x1l][x2l][x3]=p[x1l][x2l][x3-1]+nx4;
      for(long x2=x2l+1;x2<=x2h;++x2){
	p[x1l][x2]=p[x1l][x2-1]+nx3;
	p[x1l][x2][x3l]=p[x1l][x2-1][x3l]+nx3*nx4;
	for(long x3=x3l+1;x3<=x3h;++x3) p[x1l][x2][x3]=p[x1l][x2][x3-1]+nx4;
      }
      for(long x1=x1l+1;x1<=x1h;++x1) {
	p[x1]=p[x1-1]+nx2;
	p[x1][x2l]=p[x1-1][x2l]+nx2*nx3;
	p[x1][x2l][x3l]=p[x1-1][x2l][x3l]+nx2*nx3*nx4;
	for(long x3=x3l+1;x3<=x3h;++x3) p[x1][x2l][x3]=p[x1][x2l][x3-1]+nx4;
	for(long x2=x2l+1;x2<=x2h;++x2){
	  p[x1][x2]=p[x1][x2-1]+nx3;
	  p[x1][x2][x3l]=p[x1][x2-1][x3l]+nx3*nx4;
	  for(long x3=x3l+1;x3<=x3h;++x3) p[x1][x2][x3]=p[x1][x2][x3-1]+nx4;
	}
      }
      return p;
    }
  

  template<typename T> void del_rmap(T ****&p,  long const& x1l, long const& x2l, long const& x3l, long const& x4l)
    {
      //delete[] (p[x1l][x2l][x3l]+x4l);
      delete[] (p[x1l][x2l]+x3l);
      delete[] (p[x1l]+x2l);
      delete[] (p+x1l);
      p = NULL;
    }
  
  // ***************************************************************** // 
  template<typename T> T***** rmap(T *v, long const& x1l,long const& x1h,long const& x2l,long const& x2h,long const& x3l,long const& x3h,long const& x4l,long const& x4h,long const& x5l,long const& x5h)
    {
      const long nx1=x1h-x1l+1,nx2=x2h-x2l+1,nx3=x3h-x3l+1,nx4=x4h-x4l+1,nx5=x5h-x5l+1;
      T *****p=new T**** [nx1] - x1l;
      p[x1l]=new T*** [nx1*nx2] - x2l;
      p[x1l][x2l]=new T** [nx1*nx2*nx3] - x3l;
      p[x1l][x2l][x3l]=new T* [nx1*nx2*nx3*nx4] - x4l;
      p[x1l][x2l][x3l][x4l]= v - x5l;
      for(long x4=x4l+1;x4<=x4h;++x4) p[x1l][x2l][x3l][x4]=p[x1l][x2l][x3l][x4-1]+nx5;
      for(long x3=x3l+1;x3<=x3h;++x3){
	p[x1l][x2l][x3]=p[x1l][x2l][x3-1]+nx4;    
	p[x1l][x2l][x3][x4l]=p[x1l][x2l][x3-1][x4l]+nx4*nx5;
	for(long x4=x4l+1;x4<=x4h;++x4) p[x1l][x2l][x3][x4]=p[x1l][x2l][x3][x4-1]+nx5;
      }
      for(long x2=x2l+1;x2<=x2h;++x2){
	p[x1l][x2]=p[x1l][x2-1]+nx3;
	p[x1l][x2][x3l]=p[x1l][x2-1][x3l]+nx3*nx4;
	p[x1l][x2][x3l][x4l]=p[x1l][x2-1][x3l][x4l]+nx3*nx4*nx5;
	for(long x4=x4l+1;x4<=x4h;++x4) p[x1l][x2][x3l][x4]=p[x1l][x2][x3l][x4-1]+nx5;
	for(long x3=x3l+1;x3<=x3h;++x3){
	  p[x1l][x2][x3]=p[x1l][x2][x3-1]+nx4;
	  p[x1l][x2][x3][x4l]=p[x1l][x2][x3-1][x4l]+nx4*nx5;
	  for(long x4=x4l+1;x4<=x4h;++x4) p[x1l][x2][x3][x4]=p[x1l][x2][x3][x4-1]+nx5;
	}
      }	
      for(long x1=x1l+1;x1<=x1h;++x1) {
	p[x1]=p[x1-1]+nx2;
	p[x1][x2l]=p[x1-1][x2l]+nx2*nx3;
	p[x1][x2l][x3l]=p[x1-1][x2l][x3l]+nx2*nx3*nx4;
	p[x1][x2l][x3l][x4l]=p[x1-1][x2l][x3l][x4l]+nx2*nx3*nx4*nx5;
	for(long x4=x4l+1;x4<=x4h;++x4) p[x1][x2l][x3l][x4]=p[x1][x2l][x3l][x4-1]+nx5;
	for(long x3=x3l+1;x3<=x3h;++x3){
	  p[x1][x2l][x3]=p[x1][x2l][x3-1]+nx4;
	  p[x1][x2l][x3][x4l]=p[x1][x2l][x3-1][x4l]+nx4*nx5;
	  for(long x4=x4l+1;x4<=x4h;++x4) p[x1][x2l][x3][x4]=p[x1][x2l][x3][x4-1]+nx5;
	}
	for(long x2=x2l+1;x2<=x2h;++x2){
	  p[x1][x2]=p[x1][x2-1]+nx3;
	  p[x1][x2][x3l]=p[x1][x2-1][x3l]+nx3*nx4;
	  p[x1][x2][x3l][x4l]=p[x1][x2-1][x3l][x4l]+nx3*nx4*nx5;
	  for(long x4=x4l+1;x4<=x4h;++x4) p[x1][x2][x3l][x4]=p[x1][x2][x3l][x4-1]+nx5;
	  for(long x3=x3l+1;x3<=x3h;++x3){
	    p[x1][x2][x3]=p[x1][x2][x3-1]+nx4;
	    p[x1][x2][x3][x4l]=p[x1][x2][x3-1][x4l]+nx4*nx5;
	    for(long x4=x4l+1;x4<=x4h;++x4) p[x1][x2][x3][x4]=p[x1][x2][x3][x4-1]+nx5;
	  }
	}
      }
      return p;
    }
  
  template<typename T> void del_rmap(T *****&p, long const& x1l,long const& x2l,long const& x3l,long const& x4l,long const& x5l)
    {
      // delete[] (p[x1l][x2l][x3l][x4l]+x5l);
      delete[] (p[x1l][x2l][x3l]+x4l);
      delete[] (p[x1l][x2l]+x3l);
      delete[] (p[x1l]+x2l);
      delete[] (p+x1l);
      p = NULL;
    }

  // ****************************************************************** //
  
  template<typename T> T ******rmap(T *v, long const& x1l,long const& x1h,long const& x2l,long const& x2h,long const& x3l,long const& x3h,long const& x4l,long const& x4h,long const& x5l,long const& x5h,long const& x6l,long const& x6h)
    {
      const long nx1=x1h-x1l+1,nx2=x2h-x2l+1,nx3=x3h-x3l+1,nx4=x4h-x4l+1,nx5=x5h-x5l+1,nx6=x6h-x6l+1;
      T ******p;
      p=new T***** [nx1] - x1l;
      p[x1l]=new T**** [nx1*nx2] - x2l;
      p[x1l][x2l]=new T*** [nx1*nx2*nx3] - x3l;
      p[x1l][x2l][x3l]=new T** [nx1*nx2*nx3*nx4] - x4l;
      p[x1l][x2l][x3l][x4l]=new T* [nx1*nx2*nx3*nx4*nx5] - x5l;
      p[x1l][x2l][x3l][x4l][x5l]= v - x6l;
      for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2l][x3l][x4l][x5]=p[x1l][x2l][x3l][x4l][x5-1]+nx6;
      for(long x4=x4l+1;x4<=x4h;++x4){
	p[x1l][x2l][x3l][x4]=p[x1l][x2l][x3l][x4-1]+nx5;    
	p[x1l][x2l][x3l][x4][x5l]=p[x1l][x2l][x3l][x4-1][x5l]+nx5*nx6;
	for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2l][x3l][x4][x5]=p[x1l][x2l][x3l][x4][x5-1]+nx6;
      }
      for(long x3=x3l+1;x3<=x3h;++x3){
	p[x1l][x2l][x3]=p[x1l][x2l][x3-1]+nx4;
	p[x1l][x2l][x3][x4l]=p[x1l][x2l][x3-1][x4l]+nx4*nx5;
	p[x1l][x2l][x3][x4l][x5l]=p[x1l][x2l][x3-1][x4l][x5l]+nx4*nx5*nx6;
	for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2l][x3][x4l][x5]=p[x1l][x2l][x3][x4l][x5-1]+nx6;
	for(long x4=x4l+1;x4<=x4h;++x4){
	  p[x1l][x2l][x3][x4]=p[x1l][x2l][x3][x4-1]+nx5;    
	  p[x1l][x2l][x3][x4][x5l]=p[x1l][x2l][x3][x4-1][x5l]+nx5*nx6;
	  for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2l][x3][x4][x5]=p[x1l][x2l][x3][x4][x5-1]+nx6;
	}
      }
      for(long x2=x2l+1;x2<=x2h;++x2){
	p[x1l][x2]=p[x1l][x2-1]+nx3;
	p[x1l][x2][x3l]=p[x1l][x2-1][x3l]+nx3*nx4;
	p[x1l][x2][x3l][x4l]=p[x1l][x2-1][x3l][x4l]+nx3*nx4*nx5;
	p[x1l][x2][x3l][x4l][x5l]=p[x1l][x2-1][x3l][x4l][x5l]+nx3*nx4*nx5*nx6;
	for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2][x3l][x4l][x5]=p[x1l][x2][x3l][x4l][x5-1]+nx6;
	for(long x4=x4l+1;x4<=x4h;++x4){
	  p[x1l][x2][x3l][x4]=p[x1l][x2][x3l][x4-1]+nx5;    
	  p[x1l][x2][x3l][x4][x5l]=p[x1l][x2][x3l][x4-1][x5l]+nx5*nx6;
	  for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2][x3l][x4][x5]=p[x1l][x2][x3l][x4][x5-1]+nx6;
	}
	for(long x3=x3l+1;x3<=x3h;++x3){
	  p[x1l][x2][x3]=p[x1l][x2][x3-1]+nx4;
	  p[x1l][x2][x3][x4l]=p[x1l][x2][x3-1][x4l]+nx4*nx5;
	  p[x1l][x2][x3][x4l][x5l]=p[x1l][x2][x3-1][x4l][x5l]+nx4*nx5*nx6;
	  for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2][x3][x4l][x5]=p[x1l][x2][x3][x4l][x5-1]+nx6;
	  for(long x4=x4l+1;x4<=x4h;++x4){
	    p[x1l][x2][x3][x4]=p[x1l][x2][x3][x4-1]+nx5;    
	    p[x1l][x2][x3][x4][x5l]=p[x1l][x2][x3][x4-1][x5l]+nx5*nx6;
	    for(long x5=x5l+1;x5<=x5h;++x5) p[x1l][x2][x3][x4][x5]=p[x1l][x2][x3][x4][x5-1]+nx6;
	  }
	}
      }
      for(long x1=x1l+1;x1<=x1h;++x1){
	p[x1]=p[x1-1]+nx2;
	p[x1][x2l]=p[x1-1][x2l]+nx2*nx3;
	p[x1][x2l][x3l]=p[x1-1][x2l][x3l]+nx2*nx3*nx4;
	p[x1][x2l][x3l][x4l]=p[x1-1][x2l][x3l][x4l]+nx2*nx3*nx4*nx5;
	p[x1][x2l][x3l][x4l][x5l]=p[x1-1][x2l][x3l][x4l][x5l]+nx2*nx3*nx4*nx5*nx6;
	for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2l][x3l][x4l][x5]=p[x1][x2l][x3l][x4l][x5-1]+nx6;
	for(long x4=x4l+1;x4<=x4h;++x4){
	  p[x1][x2l][x3l][x4]=p[x1][x2l][x3l][x4-1]+nx5;    
	  p[x1][x2l][x3l][x4][x5l]=p[x1][x2l][x3l][x4-1][x5l]+nx5*nx6;
	  for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2l][x3l][x4][x5]=p[x1][x2l][x3l][x4][x5-1]+nx6;
	}
	for(long x3=x3l+1;x3<=x3h;++x3){
	  p[x1][x2l][x3]=p[x1][x2l][x3-1]+nx4;
	  p[x1][x2l][x3][x4l]=p[x1][x2l][x3-1][x4l]+nx4*nx5;
	  p[x1][x2l][x3][x4l][x5l]=p[x1][x2l][x3-1][x4l][x5l]+nx4*nx5*nx6;
	  for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2l][x3][x4l][x5]=p[x1][x2l][x3][x4l][x5-1]+nx6;
	  for(long x4=x4l+1;x4<=x4h;++x4){
	    p[x1][x2l][x3][x4]=p[x1][x2l][x3][x4-1]+nx5;    
	    p[x1][x2l][x3][x4][x5l]=p[x1][x2l][x3][x4-1][x5l]+nx5*nx6;
	    for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2l][x3][x4][x5]=p[x1][x2l][x3][x4][x5-1]+nx6;
	  }
	}
	for(long x2=x2l+1;x2<=x2h;++x2){
	  p[x1][x2]=p[x1][x2-1]+nx3;
	  p[x1][x2][x3l]=p[x1][x2-1][x3l]+nx3*nx4;
	  p[x1][x2][x3l][x4l]=p[x1][x2-1][x3l][x4l]+nx3*nx4*nx5;
	  p[x1][x2][x3l][x4l][x5l]=p[x1][x2-1][x3l][x4l][x5l]+nx3*nx4*nx5*nx6;
	  for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2][x3l][x4l][x5]=p[x1][x2][x3l][x4l][x5-1]+nx6;
	  for(long x4=x4l+1;x4<=x4h;++x4){
	    p[x1][x2][x3l][x4]=p[x1][x2][x3l][x4-1]+nx5;    
	    p[x1][x2][x3l][x4][x5l]=p[x1][x2][x3l][x4-1][x5l]+nx5*nx6;
	    for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2][x3l][x4][x5]=p[x1][x2][x3l][x4][x5-1]+nx6;
	  }
	  for(long x3=x3l+1;x3<=x3h;++x3){
	    p[x1][x2][x3]=p[x1][x2][x3-1]+nx4;
	    p[x1][x2][x3][x4l]=p[x1][x2][x3-1][x4l]+nx4*nx5;
	    p[x1][x2][x3][x4l][x5l]=p[x1][x2][x3-1][x4l][x5l]+nx4*nx5*nx6;
	    for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2][x3][x4l][x5]=p[x1][x2][x3][x4l][x5-1]+nx6;
	    for(long x4=x4l+1;x4<=x4h;++x4){
	      p[x1][x2][x3][x4]=p[x1][x2][x3][x4-1]+nx5;    
	      p[x1][x2][x3][x4][x5l]=p[x1][x2][x3][x4-1][x5l]+nx5*nx6;
	      for(long x5=x5l+1;x5<=x5h;++x5) p[x1][x2][x3][x4][x5]=p[x1][x2][x3][x4][x5-1]+nx6;
	    }
	  }
	}
      }
      return p;
    }
  
  template<typename T> void del_rmap(T ******&p,long const& x1l,long const& x2l,long const& x3l,long const& x4l,long const& x5l,long const& x6l)
  {
    //delete[] (p[x1l][x2l][x3l][x4l][x5l]+x6l);
    delete[] (p[x1l][x2l][x3l][x4l]+x5l);
    delete[] (p[x1l][x2l][x3l]+x4l);
    delete[] (p[x1l][x2l]+x3l);
    delete[] (p[x1l]+x2l);
    delete[] (p+x1l);
    p = NULL;
  }
  
}; 



#endif
