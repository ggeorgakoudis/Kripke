//
// Copyright (c) 2014-19, Lawrence Livermore National Security, LLC
// and Kripke project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (BSD-3-Clause)
//

#ifndef KRIPKE_ARCH_SOURCE
#define KRIPKE_ARCH_SOURCE

#include <Kripke.h>
#include <Kripke/VarTypes.h>

namespace Kripke {
namespace Arch {

template<typename AL>
struct Policy_Source;

template<typename A>
struct Policy_Source<ArchLayoutT<A, LayoutT_GDZ>> :
  Policy_Source<ArchLayoutT<A, LayoutT_DGZ>>{};

template<typename A>
struct Policy_Source<ArchLayoutT<A, LayoutT_GZD>> :
  Policy_Source<ArchLayoutT<A, LayoutT_DGZ>>{};

template<typename A>
struct Policy_Source<ArchLayoutT<A, LayoutT_ZDG>> :
  Policy_Source<ArchLayoutT<A, LayoutT_DZG>>{};

template<typename A>
struct Policy_Source<ArchLayoutT<A, LayoutT_ZGD>> :
  Policy_Source<ArchLayoutT<A, LayoutT_DZG>>{};

template<>
struct Policy_Source<ArchLayoutT<ArchT_Sequential, LayoutT_DGZ>> {
  using ExecPolicy = 
    KernelPolicy<
      Collapse<loop_exec, ArgList<0,1>, // Group, MixElem
        Lambda<0>
      >
    >;
};

template<>
struct Policy_Source<ArchLayoutT<ArchT_Sequential, LayoutT_DZG>> {
  using ExecPolicy = 
    KernelPolicy<
      Collapse<loop_exec, ArgList<0,1>, // MixElem, Group
        Lambda<0>
      >
    >;
};




#ifdef KRIPKE_USE_OPENMP

#ifdef KRIPKE_USE_APOLLO

template<>
struct Policy_Source<ArchLayoutT<ArchT_OpenMP, LayoutT_DGZ>> {
  using ExecPolicy =
    KernelPolicy<
      Collapse<apollo_collapse_exec, ArgList<0,1>, // Group, MixElem
        Lambda<0>
      >
    >;
};

template<>
struct Policy_Source<ArchLayoutT<ArchT_OpenMP, LayoutT_DZG>> {
  using ExecPolicy =
    KernelPolicy<
      Collapse<apollo_collapse_exec, ArgList<1,0>, // MixElem, Group
        Lambda<0>
      >
    >;
};

#else // not KRIPKE_USE_APOLLO

template<>
struct Policy_Source<ArchLayoutT<ArchT_OpenMP, LayoutT_DGZ>> {
  using ExecPolicy =
    KernelPolicy<
      Collapse<omp_parallel_collapse_exec, ArgList<0,1>, // Group, MixElem
        Lambda<0>
      >
    >;
};

template<>
struct Policy_Source<ArchLayoutT<ArchT_OpenMP, LayoutT_DZG>> {
  using ExecPolicy =
    KernelPolicy<
      Collapse<omp_parallel_collapse_exec, ArgList<1,0>, // MixElem, Group
        Lambda<0>
      >
    >;
};

#endif // KRIPKE_USE_APOLLO

#endif // KRIPKE_USE_OPENMP


#ifdef KRIPKE_USE_CUDA
template<>
struct Policy_Source<ArchLayoutT<ArchT_CUDA, LayoutT_DGZ>> {
  using ExecPolicy =
    KernelPolicy<
      CudaKernel<
        For<0, cuda_thread_exec,  // Group
          For<1, cuda_threadblock_exec<32>, // MixElem
            Lambda<0>
          >
        >
      >
    >;
};

template<>
struct Policy_Source<ArchLayoutT<ArchT_CUDA, LayoutT_DZG>> {
  using ExecPolicy =
    KernelPolicy<
      CudaKernel<
        For<1, cuda_threadblock_exec<32>, // MixElem
          For<0, cuda_thread_exec,  // Group
            Lambda<0>
          >
        >
      >
    >;
};
#endif // KRIPKE_USE_CUDA


}
}

#endif
