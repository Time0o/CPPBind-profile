#![allow(unused_imports)]

mod internal {
  mod c {
      use std::os::raw::c_char;

      #[link(name="api_c")]
      extern "C" {
          pub fn profile_kobject_new(mem: *mut c_char, state: i64) -> u64;
          pub fn profile_kobject_delete(ko: u64);
          pub fn profile_kobject_call(ko: u64, a: i64, b: i64, res: *mut i64) -> i64;
      }
  }

  use std::os::raw::c_char;

  pub struct Kobject {
      _mem: [c_char; 4],
      ko: u64,
  }

  impl Kobject {
      pub unsafe fn new(state: i64) -> Kobject {
          let mut mem: [c_char; 4] = [0; 4];
          let ko = c::profile_kobject_new(mem.as_mut_ptr(), state);

          Kobject { _mem: mem, ko: ko }
      }

      pub unsafe fn call(&mut self, a: i64, b: i64, res: *mut i64) -> i64 {
          c::profile_kobject_call(self.ko, a, b, res)
      }
  }

  impl Drop for Kobject {
      fn drop(&mut self) {
          unsafe {
              c::profile_kobject_delete(self.ko)
          }
      }
  }
}

pub mod profile {
    pub use super::internal::Kobject;
}
