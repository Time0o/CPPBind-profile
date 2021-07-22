mod api_c {
  #![allow(unused_imports)]
  use super::*;

  #[link(name="api_c")]
  extern "C" {
      pub fn profile_kobject_new(state: c_long) -> ProfileKobject;
      pub fn profile_kobject_delete(__self: *const ProfileKobject);
      pub fn profile_kobject_call(__self: *mut ProfileKobject, a: c_long, b: c_long, res: *mut c_long) -> c_long;
      pub fn profile_cap_base_new(c: c_ulong) -> ProfileCapBase;
      pub fn profile_cap_base_cap(__self: *mut ProfileCapBase) -> c_ulong;
      pub fn profile_cap_base_copy(_1: *const ProfileCapBase) -> ProfileCapBase;
      pub fn profile_cap_base_move(_1: *mut ProfileCapBase) -> ProfileCapBase;
      pub fn profile_cap_base_delete(__self: *const ProfileCapBase);
      pub fn profile_cap_kobject_new_1(c: c_ulong) -> ProfileCapKobject;
      pub fn profile_cap_kobject_new_2(p: *const ProfileKobject) -> ProfileCapKobject;
      pub fn profile_cap_kobject_access(__self: *const ProfileCapKobject) -> ProfileKobject;
      pub fn profile_cap_kobject_delete(__self: *const ProfileCapKobject);
      pub fn profile_cap_kobject_cap(__self: *mut ProfileCapKobject) -> c_ulong;
  }
}

#[repr(C)]
union ProfileKobjectUnion {
    mem: [c_char; 8],
    ptr: *mut c_void,
}

#[repr(C)]
pub struct ProfileKobject {
    obj : ProfileKobjectUnion,

    is_const: c_char,
    is_owning: c_char,
}

impl ProfileKobject {
    pub unsafe fn new(state: c_long) -> ProfileKobject {
        let _state: c_long;

        _state = state;

        let __ret = api_c::profile_kobject_new(_state);

        __ret
    }

    pub unsafe fn call(&mut self, a: c_long, b: c_long, res: *mut c_long) -> c_long {
        let ___self: *mut ProfileKobject;
        let _a: c_long;
        let _b: c_long;
        let _res: *mut c_long;

        ___self = self as *mut ProfileKobject;

        _a = a;

        _b = b;

        _res = res;

        let __ret = api_c::profile_kobject_call(___self, _a, _b, _res);

        __ret
    }
}

impl Drop for ProfileKobject {
    fn drop(&mut self) {
        unsafe {
            if self.is_owning == 0{
                return;
            }

            let ___self: *const ProfileKobject;

            ___self = self as *const ProfileKobject;

            api_c::profile_kobject_delete(___self)
        }
    }
}

#[repr(C)]
union ProfileCapBaseUnion {
    mem: [c_char; 8],
    ptr: *mut c_void,
}

#[repr(C)]
pub struct ProfileCapBase {
    obj : ProfileCapBaseUnion,

    is_const: c_char,
    is_owning: c_char,
}

impl ProfileCapBase {
    pub unsafe fn new(c: c_ulong) -> ProfileCapBase {
        let _c: c_ulong;

        _c = c;

        let __ret = api_c::profile_cap_base_new(_c);

        __ret
    }

    pub unsafe fn cap(&mut self) -> c_ulong {
        let ___self: *mut ProfileCapBase;

        ___self = self as *mut ProfileCapBase;

        let __ret = api_c::profile_cap_base_cap(___self);

        __ret
    }
}

impl Clone for ProfileCapBase {
    fn clone(&self) -> ProfileCapBase {
        unsafe {
            api_c::profile_cap_base_copy(self as *const ProfileCapBase)
        }
    }
}

impl Drop for ProfileCapBase {
    fn drop(&mut self) {
        unsafe {
            if self.is_owning == 0{
                return;
            }

            let ___self: *const ProfileCapBase;

            ___self = self as *const ProfileCapBase;

            api_c::profile_cap_base_delete(___self)
        }
    }
}

#[repr(C)]
union ProfileCapKobjectUnion {
    mem: [c_char; 8],
    ptr: *mut c_void,
}

#[repr(C)]
pub struct ProfileCapKobject {
    obj : ProfileCapKobjectUnion,

    is_const: c_char,
    is_owning: c_char,
}

impl ProfileCapKobject {
    pub unsafe fn new_1(c: c_ulong) -> ProfileCapKobject {
        let _c: c_ulong;

        _c = c;

        let __ret = api_c::profile_cap_kobject_new_1(_c);

        __ret
    }

    pub unsafe fn new_2(p: *const ProfileKobject) -> ProfileCapKobject {
        let _p: *const ProfileKobject;

        _p = p;

        let __ret = api_c::profile_cap_kobject_new_2(_p);

        __ret
    }

    pub unsafe fn access(&self) -> ProfileKobject {
        let ___self: *const ProfileCapKobject;

        ___self = self as *const ProfileCapKobject;

        let __ret = api_c::profile_cap_kobject_access(___self);

        __ret
    }

    pub unsafe fn cap(&mut self) -> c_ulong {
        let ___self: *mut ProfileCapKobject;

        ___self = self as *mut ProfileCapKobject;

        let __ret = api_c::profile_cap_kobject_cap(___self);

        __ret
    }
}

impl Drop for ProfileCapKobject {
    fn drop(&mut self) {
        unsafe {
            if self.is_owning == 0{
                return;
            }

            let ___self: *const ProfileCapKobject;

            ___self = self as *const ProfileCapKobject;

            api_c::profile_cap_kobject_delete(___self)
        }
    }
}