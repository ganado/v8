// Copyright 2016 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_FIELD_TYPE_H_
#define V8_FIELD_TYPE_H_

#include "src/objects.h"
#include "src/objects/heap-object.h"
#include "src/objects/map.h"

namespace v8 {
namespace internal {

template <typename T>
class Handle;

class FieldType : public ObjectPtr {
 public:
  static FieldType None();
  static FieldType Any();
  static Handle<FieldType> None(Isolate* isolate);
  static Handle<FieldType> Any(Isolate* isolate);
  static FieldType Class(Map map);
  static Handle<FieldType> Class(Handle<Map> map, Isolate* isolate);
  static FieldType cast(Object object);
  static FieldType unchecked_cast(ObjectPtr object) {
    return FieldType(object.ptr());
  }

  bool NowContains(Object value) const;

  bool NowContains(Handle<Object> value) const { return NowContains(*value); }

  bool IsClass() const;
  Map AsClass() const;
  bool IsNone() const { return *this == None(); }
  bool IsAny() const { return *this == Any(); }
  bool NowStable() const;
  bool NowIs(FieldType other) const;
  bool NowIs(Handle<FieldType> other) const;

  void PrintTo(std::ostream& os) const;

  FieldType* operator->() { return this; }
  const FieldType* operator->() const { return this; }

 private:
  explicit constexpr FieldType(Address ptr) : ObjectPtr(ptr) {}
};

}  // namespace internal
}  // namespace v8

#endif  // V8_FIELD_TYPE_H_
