# Assignment 5 CO5 – Part A Design Notes

This file records the design/pseudocode deliverables for Part A. The assignment explicitly asks for UML/vtable diagrams, hierarchy design and pseudocode; these written deliverables are not replaced by C++ programs. Runnable prediction programs for A2 and A5 are supplied separately.

## A1 – Polymorphic Bill hierarchy

**Common data:** patient identifier/name. **Common operations:** `total() const`, `type() const`, and a non-virtual `print()` that calls the two virtual operations.

```text
                 <<abstract>> Bill
        - patient : string
        + total() : double {pure virtual}
        + type() : string {pure virtual}
        + print() : void
          /            |            |             \
 OutPatientBill  InPatientBill  DayCareBill  EmergencyBill
```

**Daily-total pseudocode**

```text
SET dayTotal TO 0
FOR EACH billPointer IN bills
    dayTotal <- dayTotal + billPointer.total()
END FOR
DISPLAY dayTotal
```

A type-field/switch design also totals n bills in O(n), but every new bill kind requires edits to the switch and the central data structure. With the hierarchy, a new derived bill can be introduced while keeping the loop unchanged.

## A2 – Runtime binding and vtable sketch

`Bill* b = new OPBill; b->show();` calls the non-virtual `show()` selected at compile time. Inside `show()`, the virtual call `total()` is dynamically dispatched to `OPBill::total()`.

```text
Bill vtable:        [destructor] [total -> pure virtual]
OPBill vtable:      [~OPBill]   [total -> OPBill::total]
InPatient vtable:   [~InPatient][total -> InPatientBill::total]
```

The virtual destructor ensures `delete BillPointer` runs the derived destructor before the base destructor.

## A3 – Payer hierarchy

```text
                   <<abstract>> Payer
              + amountCovered(const Bill&) : double
                  /          |            \
              SelfPay     Insurance   GovernmentScheme
```

A future corporate payer is added as another `Payer` implementation. The billing loop depends on the interface only.

## A4 – Exception hierarchy and specifications

```text
std::exception
    |
std::runtime_error
    |
BillingError
  |-- ClaimError
  |-- PackageError
```

Validation, parsing, missing-patient and claim functions may throw. Destructors and simple observers should be `noexcept`; destructors should not throw because a second exception during stack unwinding can terminate the program. Allocation failures are reported by `std::bad_alloc`.

## A5 – Recovery pseudocode

```text
FUNCTION settleClaim(bill, cover)
    TRY
        RETURN approve(bill, cover)
    CATCH ClaimError error
        LOG error.message
        THROW                 // preserve the original exception type
    END TRY
END FUNCTION

AT TOP LEVEL
    TRY
        CALL settleClaim(...)
    CATCH std::exception error
        DISPLAY user-safe error.message
    CATCH ALL
        DISPLAY "Unexpected error"
    END TRY
```

RAII objects own files, memory and other resources. During exception propagation, stack unwinding destroys local objects automatically, releasing their resources.

## B3/B4 design choices

- The benchmark source compares a virtual interface, a tagged switch and `std::variant`/`std::visit` using the same two bill calculations.
- The production extension adds a new derived bill and a new payer without changing the base classes or existing implementations.
- Timings are machine/compiler dependent. Run the benchmark with `-O2` and record the values from your own system rather than treating sample timings as universal.
