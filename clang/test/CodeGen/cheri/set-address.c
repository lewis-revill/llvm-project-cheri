// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// REQUIRES: mips-registered-target

// RUN: %cheri_cc1 %s -o - -emit-llvm | %cheri_FileCheck %s -check-prefix=HYBRID
// RUN: %cheri_purecap_cc1 %s -o - -emit-llvm | %cheri_FileCheck %s -check-prefix=PURECAP

typedef __SIZE_TYPE__ ptraddr_t;
// The existing inline function macro from cheric.h
static __attribute__((always_inline)) inline void *__capability
cheri_setaddress(const void *__capability dst, ptraddr_t addr) {
  return (__builtin_cheri_offset_increment(dst, addr - __builtin_cheri_address_get(dst)));
}

// HYBRID-LABEL: define {{[^@]+}}@use_sys_cheric_function
// HYBRID-SAME: (i8 addrspace(200)* [[IN:%.*]], i64 zeroext [[NEW_ADDR:%.*]]) #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    [[DST_ADDR_I:%.*]] = alloca i8 addrspace(200)*, align 16
// HYBRID-NEXT:    [[ADDR_ADDR_I:%.*]] = alloca i64, align 8
// HYBRID-NEXT:    [[IN_ADDR:%.*]] = alloca i8 addrspace(200)*, align 16
// HYBRID-NEXT:    [[NEW_ADDR_ADDR:%.*]] = alloca i64, align 8
// HYBRID-NEXT:    store i8 addrspace(200)* [[IN]], i8 addrspace(200)** [[IN_ADDR]], align 16
// HYBRID-NEXT:    store i64 [[NEW_ADDR]], i64* [[NEW_ADDR_ADDR]], align 8
// HYBRID-NEXT:    [[TMP0:%.*]] = load i8 addrspace(200)*, i8 addrspace(200)** [[IN_ADDR]], align 16
// HYBRID-NEXT:    [[TMP1:%.*]] = load i64, i64* [[NEW_ADDR_ADDR]], align 8
// HYBRID-NEXT:    store i8 addrspace(200)* [[TMP0]], i8 addrspace(200)** [[DST_ADDR_I]], align 16
// HYBRID-NEXT:    store i64 [[TMP1]], i64* [[ADDR_ADDR_I]], align 8
// HYBRID-NEXT:    [[TMP2:%.*]] = load i8 addrspace(200)*, i8 addrspace(200)** [[DST_ADDR_I]], align 16
// HYBRID-NEXT:    [[TMP3:%.*]] = load i64, i64* [[ADDR_ADDR_I]], align 8
// HYBRID-NEXT:    [[TMP4:%.*]] = load i8 addrspace(200)*, i8 addrspace(200)** [[DST_ADDR_I]], align 16
// HYBRID-NEXT:    [[TMP5:%.*]] = call i64 @llvm.cheri.cap.address.get.i64(i8 addrspace(200)* [[TMP4]]) #2
// HYBRID-NEXT:    [[SUB_I:%.*]] = sub i64 [[TMP3]], [[TMP5]]
// HYBRID-NEXT:    [[__BUILTIN_CHERI_OFFSET_INCREMENT_I:%.*]] = getelementptr i8, i8 addrspace(200)* [[TMP2]], i64 [[SUB_I]]
// HYBRID-NEXT:    ret i8 addrspace(200)* [[__BUILTIN_CHERI_OFFSET_INCREMENT_I]]
//
// PURECAP-LABEL: define {{[^@]+}}@use_sys_cheric_function
// PURECAP-SAME: (i8 addrspace(200)* [[IN:%.*]], i64 zeroext [[NEW_ADDR:%.*]]) addrspace(200) #0
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[DST_ADDR_I:%.*]] = alloca i8 addrspace(200)*, align 16, addrspace(200)
// PURECAP-NEXT:    [[ADDR_ADDR_I:%.*]] = alloca i64, align 8, addrspace(200)
// PURECAP-NEXT:    [[IN_ADDR:%.*]] = alloca i8 addrspace(200)*, align 16, addrspace(200)
// PURECAP-NEXT:    [[NEW_ADDR_ADDR:%.*]] = alloca i64, align 8, addrspace(200)
// PURECAP-NEXT:    store i8 addrspace(200)* [[IN]], i8 addrspace(200)* addrspace(200)* [[IN_ADDR]], align 16
// PURECAP-NEXT:    store i64 [[NEW_ADDR]], i64 addrspace(200)* [[NEW_ADDR_ADDR]], align 8
// PURECAP-NEXT:    [[TMP0:%.*]] = load i8 addrspace(200)*, i8 addrspace(200)* addrspace(200)* [[IN_ADDR]], align 16
// PURECAP-NEXT:    [[TMP1:%.*]] = load i64, i64 addrspace(200)* [[NEW_ADDR_ADDR]], align 8
// PURECAP-NEXT:    store i8 addrspace(200)* [[TMP0]], i8 addrspace(200)* addrspace(200)* [[DST_ADDR_I]], align 16
// PURECAP-NEXT:    store i64 [[TMP1]], i64 addrspace(200)* [[ADDR_ADDR_I]], align 8
// PURECAP-NEXT:    [[TMP2:%.*]] = load i8 addrspace(200)*, i8 addrspace(200)* addrspace(200)* [[DST_ADDR_I]], align 16
// PURECAP-NEXT:    [[TMP3:%.*]] = load i64, i64 addrspace(200)* [[ADDR_ADDR_I]], align 8
// PURECAP-NEXT:    [[TMP4:%.*]] = load i8 addrspace(200)*, i8 addrspace(200)* addrspace(200)* [[DST_ADDR_I]], align 16
// PURECAP-NEXT:    [[TMP5:%.*]] = call i64 @llvm.cheri.cap.address.get.i64(i8 addrspace(200)* [[TMP4]]) #2
// PURECAP-NEXT:    [[SUB_I:%.*]] = sub i64 [[TMP3]], [[TMP5]]
// PURECAP-NEXT:    [[__BUILTIN_CHERI_OFFSET_INCREMENT_I:%.*]] = getelementptr i8, i8 addrspace(200)* [[TMP2]], i64 [[SUB_I]]
// PURECAP-NEXT:    ret i8 addrspace(200)* [[__BUILTIN_CHERI_OFFSET_INCREMENT_I]]
//
void *__capability use_sys_cheric_function(void *__capability in, ptraddr_t new_addr) {
  return cheri_setaddress(in, new_addr);
  // ASM-LABEL: .ent use_sys_cheric_function
  // ASM: csetaddr $c3, $c3, $4
  // ASM: .end use_sys_cheric_function
}

// HYBRID-LABEL: define {{[^@]+}}@use_builtin_function
// HYBRID-SAME: (i8 addrspace(200)* [[IN:%.*]], i64 zeroext [[NEW_ADDR:%.*]]) #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    [[IN_ADDR:%.*]] = alloca i8 addrspace(200)*, align 16
// HYBRID-NEXT:    [[NEW_ADDR_ADDR:%.*]] = alloca i64, align 8
// HYBRID-NEXT:    store i8 addrspace(200)* [[IN]], i8 addrspace(200)** [[IN_ADDR]], align 16
// HYBRID-NEXT:    store i64 [[NEW_ADDR]], i64* [[NEW_ADDR_ADDR]], align 8
// HYBRID-NEXT:    [[TMP0:%.*]] = load i8 addrspace(200)*, i8 addrspace(200)** [[IN_ADDR]], align 16
// HYBRID-NEXT:    [[TMP1:%.*]] = load i64, i64* [[NEW_ADDR_ADDR]], align 8
// HYBRID-NEXT:    [[TMP2:%.*]] = call i8 addrspace(200)* @llvm.cheri.cap.address.set.i64(i8 addrspace(200)* [[TMP0]], i64 [[TMP1]])
// HYBRID-NEXT:    ret i8 addrspace(200)* [[TMP2]]
//
// PURECAP-LABEL: define {{[^@]+}}@use_builtin_function
// PURECAP-SAME: (i8 addrspace(200)* [[IN:%.*]], i64 zeroext [[NEW_ADDR:%.*]]) addrspace(200) #0
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[IN_ADDR:%.*]] = alloca i8 addrspace(200)*, align 16, addrspace(200)
// PURECAP-NEXT:    [[NEW_ADDR_ADDR:%.*]] = alloca i64, align 8, addrspace(200)
// PURECAP-NEXT:    store i8 addrspace(200)* [[IN]], i8 addrspace(200)* addrspace(200)* [[IN_ADDR]], align 16
// PURECAP-NEXT:    store i64 [[NEW_ADDR]], i64 addrspace(200)* [[NEW_ADDR_ADDR]], align 8
// PURECAP-NEXT:    [[TMP0:%.*]] = load i8 addrspace(200)*, i8 addrspace(200)* addrspace(200)* [[IN_ADDR]], align 16
// PURECAP-NEXT:    [[TMP1:%.*]] = load i64, i64 addrspace(200)* [[NEW_ADDR_ADDR]], align 8
// PURECAP-NEXT:    [[TMP2:%.*]] = call i8 addrspace(200)* @llvm.cheri.cap.address.set.i64(i8 addrspace(200)* [[TMP0]], i64 [[TMP1]])
// PURECAP-NEXT:    ret i8 addrspace(200)* [[TMP2]]
//
void *__capability use_builtin_function(void *__capability in, ptraddr_t new_addr) {
  return __builtin_cheri_address_set(in, new_addr);
  // ASM-LABEL: .ent use_builtin_function
  // ASM: csetaddr $c3, $c3, $4
  // ASM: .end use_builtin_function
}

// HYBRID-LABEL: define {{[^@]+}}@use_asm
// HYBRID-SAME: (i8 addrspace(200)* [[IN:%.*]], i64 zeroext [[NEW_ADDR:%.*]]) #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    [[IN_ADDR:%.*]] = alloca i8 addrspace(200)*, align 16
// HYBRID-NEXT:    [[NEW_ADDR_ADDR:%.*]] = alloca i64, align 8
// HYBRID-NEXT:    [[RESULT:%.*]] = alloca i8 addrspace(200)*, align 16
// HYBRID-NEXT:    store i8 addrspace(200)* [[IN]], i8 addrspace(200)** [[IN_ADDR]], align 16
// HYBRID-NEXT:    store i64 [[NEW_ADDR]], i64* [[NEW_ADDR_ADDR]], align 8
// HYBRID-NEXT:    [[TMP0:%.*]] = load i8 addrspace(200)*, i8 addrspace(200)** [[IN_ADDR]], align 16
// HYBRID-NEXT:    [[TMP1:%.*]] = load i64, i64* [[NEW_ADDR_ADDR]], align 8
// HYBRID-NEXT:    [[TMP2:%.*]] = call i8 addrspace(200)* asm "csetaddr $0, $1, $2\0A\09", "=C,C,r,~{$1}"(i8 addrspace(200)* [[TMP0]], i64 [[TMP1]]) #3, !srcloc !2
// HYBRID-NEXT:    store i8 addrspace(200)* [[TMP2]], i8 addrspace(200)** [[RESULT]], align 16
// HYBRID-NEXT:    [[TMP3:%.*]] = load i8 addrspace(200)*, i8 addrspace(200)** [[RESULT]], align 16
// HYBRID-NEXT:    ret i8 addrspace(200)* [[TMP3]]
//
// PURECAP-LABEL: define {{[^@]+}}@use_asm
// PURECAP-SAME: (i8 addrspace(200)* [[IN:%.*]], i64 zeroext [[NEW_ADDR:%.*]]) addrspace(200) #0
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[IN_ADDR:%.*]] = alloca i8 addrspace(200)*, align 16, addrspace(200)
// PURECAP-NEXT:    [[NEW_ADDR_ADDR:%.*]] = alloca i64, align 8, addrspace(200)
// PURECAP-NEXT:    [[RESULT:%.*]] = alloca i8 addrspace(200)*, align 16, addrspace(200)
// PURECAP-NEXT:    store i8 addrspace(200)* [[IN]], i8 addrspace(200)* addrspace(200)* [[IN_ADDR]], align 16
// PURECAP-NEXT:    store i64 [[NEW_ADDR]], i64 addrspace(200)* [[NEW_ADDR_ADDR]], align 8
// PURECAP-NEXT:    [[TMP0:%.*]] = load i8 addrspace(200)*, i8 addrspace(200)* addrspace(200)* [[IN_ADDR]], align 16
// PURECAP-NEXT:    [[TMP1:%.*]] = load i64, i64 addrspace(200)* [[NEW_ADDR_ADDR]], align 8
// PURECAP-NEXT:    [[TMP2:%.*]] = call i8 addrspace(200)* asm "csetaddr $0, $1, $2\0A\09", "=C,C,r,~{$1}"(i8 addrspace(200)* [[TMP0]], i64 [[TMP1]]) #3, !srcloc !2
// PURECAP-NEXT:    store i8 addrspace(200)* [[TMP2]], i8 addrspace(200)* addrspace(200)* [[RESULT]], align 16
// PURECAP-NEXT:    [[TMP3:%.*]] = load i8 addrspace(200)*, i8 addrspace(200)* addrspace(200)* [[RESULT]], align 16
// PURECAP-NEXT:    ret i8 addrspace(200)* [[TMP3]]
//
void *__capability use_asm(void *__capability in, ptraddr_t new_addr) {
  void *__capability result;
  __asm__ ("csetaddr %0, %1, %2\n\t" :"=C"(result) : "C"(in), "r"(new_addr));
  return result;
  // ASM-LABEL: .ent use_asm
  // ASM: csetaddr $c3, $c3, $4
  // ASM: .end use_asm
}
