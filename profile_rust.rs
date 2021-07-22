#![feature(llvm_asm)]

use std::ffi::*;
use std::os::raw::*;

include!("api_rust.rs");

const NUM_RUNS : usize = 10000;
const NUM_LOOPS : usize = 100000;
const NUM_LOOPS_WARMUP : usize = 100;

macro_rules! get_cycles{
  ($high:expr,$low:expr)=>{
    {
      unsafe {
        llvm_asm!("LFENCE\n\t
             RDTSC\n\t
             MOV %edx, $0\n\t
             MOV %eax, $1\n\t
             LFENCE\n\t"
             : "=r" ($high), "=r" ($low)
             :: "rax", "rbx", "rcx", "rdx"
             : "volatile");
      }
    }
  }
}

#[no_mangle]
#[inline(never)]
fn ipc_call(state: i64, a: i64, b: i64) -> i64
{
  let mut res: i64 = 0;

  unsafe {
    let ko = ProfileKobject::new(state);

    let cap = ProfileCapKobject::new_2(&ko);

    cap.access().call(a, b, &mut res);
  }

  res
}

fn main()
{
  let state: i64 = 0;
  let a: i64 = 2;
  let b: i64 = 3;
  let mut _res: i64 = 0;

  let mut cycles : [u64; NUM_LOOPS + NUM_LOOPS_WARMUP] = [0; NUM_LOOPS + NUM_LOOPS_WARMUP];
  let mut cycles_mins : [u64; NUM_RUNS] = [0; NUM_RUNS];

  let mut cycles_low_start : i32;
  let mut cycles_high_start : i32;
  let mut cycles_low_end : i32;
  let mut cycles_high_end : i32;

  for r in 0..NUM_RUNS {
    for l in 0..(NUM_LOOPS + NUM_LOOPS_WARMUP) {
      get_cycles!(cycles_high_start, cycles_low_start);

      _res = ipc_call(state, a, b);

      get_cycles!(cycles_high_end, cycles_low_end);

      let start : u64 = ((cycles_high_start as u64) << 32) | ((cycles_low_start as u64) & 0xffffffff);
      let end : u64= ((cycles_high_end as u64) << 32) | ((cycles_low_end as u64) & 0xffffffff);

      cycles[l] = end - start;
    }

    cycles_mins[r] = cycles[NUM_LOOPS_WARMUP];
    for l in (NUM_LOOPS_WARMUP + 1)..(NUM_LOOPS + NUM_LOOPS_WARMUP) {
      if cycles[l] < cycles_mins[r] {
        cycles_mins[r] = cycles[l];
      }
    }
  }

  for r in 0..NUM_RUNS {
    println!("{}", cycles_mins[r]);
  }
}
