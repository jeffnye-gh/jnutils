# RVA23U64
```
rv64gacv_zbb_zbc_zbs_zicntr_zihpm_ziccif_ziccrse_ziccamoa_zicclsm_za64rs_zihintpause_zic64b_zicbom_zicbop_zicboz_zfhmin_zkt_zvfhmin_zvbb_zvkt_zihintntl_zicond_zcmop_zcb_zfa_zawrs
```

GCC option
g           - *I* (implied by RVA23U64)
g           - *M* Integer multiplication and division.
a           - *A* Atomic instructions.
g           - *F* Single-precision floating-point instructions.
g           - *D* Double-precision floating-point instructions.
c           - *C* Compressed instructions.
zbb_zbc_zbs - *B* Bit-manipulation instructions.
g           - *Zicsr*  CSR instructions.  These are implied by presence of F.
zicntr      - *Zicntr* Base counters and timers.
zihpm       - *Zihpm* Hardware performance counters.
Ziccif      - *Ziccif* 
Ziccrse     - *Ziccrse* 
Ziccamoa    - *Ziccamoa* 
Zicclsm     - *Zicclsm* 
Za64rs      - *Za64rs* 
Zihintpause - *Zihintpause*
Zic64b      - *Zic64b* 
Zicbom      - *Zicbom* Cache-block management instructions.
Zicbop      - *Zicbop* Cache-block prefetch instructions.
Zicboz      - *Zicboz* Cache-Block Zero Instructions.
Zfhmin      - *Zfhmin* Half-precision floating-point.
zkt         - *Zkt* Data-independent execution latency.
v           - *V* Vector extension. also includes
              zvl128b and smaller
Zvfhmin     - *Zvfhmin* Vector minimal half-precision floating-point.
Zvbb        - *Zvbb* Vector basic bit-manipulation instructions.
zvkt        - *Zvkt* Vector data-independent execution latency.
Zihintntl   - *Zihintntl* Non-temporal locality hints.
zicond      - *Zicond* Integer conditional operations.
???         - *Zimop* may-be-operations.
Zcmop       - *Zcmop* Compressed may-be-operations.
zcb         - *Zcb* Additional compressed instructions.
zfa         - *Zfa* Additional floating-Point instructions.
zawrs       - *Zawrs* Wait-on-reservation-set instructions.
???         - *Supm* 

# RVA23U64 Optional
## Localized
zvkng  - *Zvkng* Vector crypto NIST algorithms with GCM.
zvksg  - *Zvksg* Vector crypto ShangMi algorithms with GCM.

## Development (experimental)
???    - *Zabha* Byte and halfword atomic memory operations.
???    - *Zacas* Compare-and-Swap instructions.
???    - *Ziccamoc* Main mem regions with cacheability and coherence PMAs
zvbc   - *Zvbc* Vector carryless multiplication.
???    - *Zama16b* Misaligned loads, stores, and AMOs to main memory 

## Expansion (standardized, but not required)
zfh      - *Zfh* Scalar half-precision floating-point.
zbc      - *Zbc* Scalar carryless multiply.
???      - *Zicfilp* Landing Pads.
???      - *Zicfiss* Shadow Stack.
Zvfh     - *Zvfh* Vector half-precision floating-point.
???      - *Zfbfmin* Scalar BF16 converts.
Zvfbfmin - *Zvfbfmin* Vector BF16 converts.
???      - *Zvfbfwma* Vector BF16 widening mul-add.

# RVA23S64

          - ALL of RVA23U64
Zifencei  - *Zifencei*  Instruction-Fetch Fence.
???       - *Ss1p13*  Supervisor architecture version 1.13. 
???       - *Svbare* The `satp` mode Bare must be supported.
???       - *Sv39* Page-based 39-bit virtual-Memory system.
???       - *Svade* Page-fault exceptions are raised when a page ...
???       - *Ssccptr* 
???       - *Sstvecd* 
???       - *Sstvala* 
???       - *Sscounterenw* 
Svpbmt    - *Svpbmt* Page-based memory types
Svinval   - *Svinval* Fine-grained address-translation cache invalidation.
Svnapot   - *Svnapot* NAPOT translation contiguity.
sstc      - *Sstc* supervisor-mode timer interrupts.
Sscofpmf  - *Sscofpmf* count overflow and mode-based filtering.
???       - *Ssnpm* 
???       - *Ssu64xl* 
???       - *Sha* The augmented hypervisor extension. sha comprises:
         
h           ** *H* The hypervisor extension.
Ssstateen   ** *Ssstateen* Supervisor-mode view of the state-enable 
???         ** *Shcounterenw* 
???         ** *Shvstvala* 
???         ** *Shtvala* `htval` 
???         ** *Shvstvecd* 
???         ** *Shvsatpa* 
???         ** *Shgatpa* 

# RVA23S64 Optional Extensions

## Localized Options - none
## Development Options - none
## Expansion Options

???    - *Sv48* Page-based 48-bit virtual-memory system.
???    - *Sv57* Page-based 57-bit virtual-memory system.
zkr    - *Zkr*  Entropy CSR.
???    - *Svadu* Hardware A/D bit updates.
???    - *Sdtrig* Debug triggers.
???    - *Ssstrict* 
???    - *Svvptc* 
???    - *Sspm* 

