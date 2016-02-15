/* Interrupt */
#define IDT_ENTRY_MAX 128

#define IDT_FLAGS_NONE 0x0
#define IDT_FLAGS_VALID 0x1
#define IDT_FLAGS_ENABLE 0x2

#define IDT_KEYBOARD_NUM 5

/* IDT Entry struct */
typedef volatile struct _idt_entry {
  unsigned int flags;
  void (*handler)(void);
} idt_entry;

idt_entry *idt_setup(void);
void idt_entry_setup(idt_entry *idt, unsigned int num, void (*handler)(void));
void idt_entry_enable(idt_entry *idt, unsigned int num);

/* inline function */
static inline __attribute__((always_inline)) void interrupt_enable(void)
{
  __asm__("srieiw 1");
}

static inline __attribute__((always_inline)) void interrupt_disable(void)
{
  __asm__("srieiw 0");
}

static inline __attribute__((always_inline)) void idt_set(idt_entry *idtr)
{
  __asm__("sridtw %0" : : "r"(idtr));
}

static inline __attribute__((always_inline)) void idt_load(void)
{
  __asm__("idts");
}
