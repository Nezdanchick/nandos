#include <interrupts.h>
#include <stdbool.h>
#define KERNEL_CODE_SEGMENT_SELECTOR 0x08

typedef struct
{
    uint16_t offset_0_15;
    uint16_t segment_selector;
    uint8_t ist;
    uint8_t flags;
    uint16_t offset_16_31;
    uint32_t offset_32_63;
    uint32_t reserved;
} __attribute__((__packed__)) idt_entry_t;

typedef struct __attribute__((__packed__))
{
    const uint16_t limit;
    const idt_entry_t *data;
} idt_pointer_t;

const int PRESENT_OFFSET = 7;
const int DPL_OFFSET = 5;
const int INTERRUPT_TYPE_OFFSET = 0;

idt_entry_t idt_data[256];
const idt_pointer_t idt = {
    .data = idt_data,
    .limit = sizeof(idt_data) - 1,
};

uint8_t gen_interrupt_descriptor_flags(bool is_present,
                                       uint8_t dpl,
                                       bool is_trap_gate)
{

    return ((is_present & 1) << PRESENT_OFFSET) |
           ((dpl & 0b11) << DPL_OFFSET) |
           ((is_trap_gate & 1) << INTERRUPT_TYPE_OFFSET) |
           0b1110;
}

idt_entry_t gen_interrupt_descriptor(uint16_t segment_selector,
                                     uint64_t offset,
                                     bool is_present,
                                     uint8_t dpl,
                                     bool is_trap_gate)
{
    idt_entry_t result = {
        .offset_0_15 = offset & 0xFFFF,
        .segment_selector = segment_selector,
        .ist = 0,
        .flags = gen_interrupt_descriptor_flags(is_present, dpl, is_trap_gate),
        .offset_16_31 = (offset >> 16) & 0xFFFF,
        .offset_32_63 = (offset >> 32) & 0xFFFFFFFF,
        .reserved = 0};

    return result;
}

#define SET_USER_ISR(i)                                                  \
    extern void isr_##i();                                               \
    idt_data[i] = gen_interrupt_descriptor(KERNEL_CODE_SEGMENT_SELECTOR, \
                                           (uint64_t)isr_##i, true, 3, false)

#define SET_KERNEL_ISR(i)                                                \
    extern void isr_##i();                                               \
    idt_data[i] = gen_interrupt_descriptor(KERNEL_CODE_SEGMENT_SELECTOR, \
                                           (uint64_t)isr_##i, true, 0, false)

#define SET_ERROR_ISR(i)                                                       \
    extern void esr_##i();                                               \
    idt_data[i] = gen_interrupt_descriptor(KERNEL_CODE_SEGMENT_SELECTOR, \
                                           (uint64_t)esr_##i, true, 3, false)

void idt_init(void)
{
    SET_ERROR_ISR(0);
    SET_ERROR_ISR(1);
    SET_ERROR_ISR(2);
    SET_ERROR_ISR(3);
    SET_ERROR_ISR(4);
    SET_ERROR_ISR(5);
    SET_ERROR_ISR(6);
    SET_ERROR_ISR(7);
    SET_ERROR_ISR(8);
    SET_ERROR_ISR(9);
    SET_ERROR_ISR(10);
    SET_ERROR_ISR(11);
    SET_ERROR_ISR(12);
    SET_ERROR_ISR(13);
    SET_ERROR_ISR(14);
    SET_ERROR_ISR(15);
    SET_ERROR_ISR(16);
    SET_ERROR_ISR(17);
    SET_ERROR_ISR(18);
    SET_ERROR_ISR(19);
    SET_ERROR_ISR(20);
    SET_ERROR_ISR(21);
    SET_ERROR_ISR(22);
    SET_ERROR_ISR(23);
    SET_ERROR_ISR(24);
    SET_ERROR_ISR(25);
    SET_ERROR_ISR(26);
    SET_ERROR_ISR(27);
    SET_ERROR_ISR(28);
    SET_ERROR_ISR(29);
    SET_ERROR_ISR(30);
    SET_ERROR_ISR(31);

    SET_KERNEL_ISR(32);
    SET_KERNEL_ISR(33);
    SET_KERNEL_ISR(34);
    SET_KERNEL_ISR(35);
    SET_KERNEL_ISR(36);
    SET_KERNEL_ISR(37);
    SET_KERNEL_ISR(38);
    SET_KERNEL_ISR(39);
    SET_KERNEL_ISR(40);
    SET_KERNEL_ISR(41);
    SET_KERNEL_ISR(42);
    SET_KERNEL_ISR(43);
    SET_KERNEL_ISR(44);
    SET_KERNEL_ISR(45);
    SET_KERNEL_ISR(46);
    SET_KERNEL_ISR(47);

    SET_KERNEL_ISR(48);
    SET_KERNEL_ISR(49);
    SET_KERNEL_ISR(50);
    SET_KERNEL_ISR(51);
    SET_KERNEL_ISR(52);
    SET_KERNEL_ISR(53);
    SET_KERNEL_ISR(54);
    SET_KERNEL_ISR(55);
    SET_KERNEL_ISR(56);
    SET_KERNEL_ISR(57);
    SET_KERNEL_ISR(58);
    SET_KERNEL_ISR(59);
    SET_KERNEL_ISR(60);
    SET_KERNEL_ISR(61);
    SET_KERNEL_ISR(62);
    SET_KERNEL_ISR(63);
    SET_KERNEL_ISR(64);
    SET_KERNEL_ISR(65);
    SET_KERNEL_ISR(66);
    SET_KERNEL_ISR(67);
    SET_KERNEL_ISR(68);
    SET_KERNEL_ISR(69);
    SET_KERNEL_ISR(70);
    SET_KERNEL_ISR(71);
    SET_KERNEL_ISR(72);
    SET_KERNEL_ISR(73);
    SET_KERNEL_ISR(74);
    SET_KERNEL_ISR(75);
    SET_KERNEL_ISR(76);
    SET_KERNEL_ISR(77);
    SET_KERNEL_ISR(78);
    SET_KERNEL_ISR(79);
    SET_KERNEL_ISR(80);
    SET_KERNEL_ISR(81);
    SET_KERNEL_ISR(82);
    SET_KERNEL_ISR(83);
    SET_KERNEL_ISR(84);
    SET_KERNEL_ISR(85);
    SET_KERNEL_ISR(86);
    SET_KERNEL_ISR(87);
    SET_KERNEL_ISR(88);
    SET_KERNEL_ISR(89);
    SET_KERNEL_ISR(90);
    SET_KERNEL_ISR(91);
    SET_KERNEL_ISR(92);
    SET_KERNEL_ISR(93);
    SET_KERNEL_ISR(94);
    SET_KERNEL_ISR(95);
    SET_KERNEL_ISR(96);
    SET_KERNEL_ISR(97);
    SET_KERNEL_ISR(98);
    SET_KERNEL_ISR(99);
    SET_KERNEL_ISR(100);
    SET_KERNEL_ISR(101);
    SET_KERNEL_ISR(102);
    SET_KERNEL_ISR(103);
    SET_KERNEL_ISR(104);
    SET_KERNEL_ISR(105);
    SET_KERNEL_ISR(106);
    SET_KERNEL_ISR(107);
    SET_KERNEL_ISR(108);
    SET_KERNEL_ISR(109);
    SET_KERNEL_ISR(110);
    SET_KERNEL_ISR(111);
    SET_KERNEL_ISR(112);
    SET_KERNEL_ISR(113);
    SET_KERNEL_ISR(114);
    SET_KERNEL_ISR(115);
    SET_KERNEL_ISR(116);
    SET_KERNEL_ISR(117);
    SET_KERNEL_ISR(118);
    SET_KERNEL_ISR(119);
    SET_KERNEL_ISR(120);
    SET_KERNEL_ISR(121);
    SET_KERNEL_ISR(122);
    SET_KERNEL_ISR(123);
    SET_KERNEL_ISR(124);
    SET_KERNEL_ISR(125);
    SET_KERNEL_ISR(126);
    SET_KERNEL_ISR(127);

    SET_USER_ISR(128);

    SET_KERNEL_ISR(129);
    SET_KERNEL_ISR(130);
    SET_KERNEL_ISR(131);
    SET_KERNEL_ISR(132);
    SET_KERNEL_ISR(133);
    SET_KERNEL_ISR(134);
    SET_KERNEL_ISR(135);
    SET_KERNEL_ISR(136);
    SET_KERNEL_ISR(137);
    SET_KERNEL_ISR(138);
    SET_KERNEL_ISR(139);
    SET_KERNEL_ISR(140);
    SET_KERNEL_ISR(141);
    SET_KERNEL_ISR(142);
    SET_KERNEL_ISR(143);
    SET_KERNEL_ISR(144);
    SET_KERNEL_ISR(145);
    SET_KERNEL_ISR(146);
    SET_KERNEL_ISR(147);
    SET_KERNEL_ISR(148);
    SET_KERNEL_ISR(149);
    SET_KERNEL_ISR(150);
    SET_KERNEL_ISR(151);
    SET_KERNEL_ISR(152);
    SET_KERNEL_ISR(153);
    SET_KERNEL_ISR(154);
    SET_KERNEL_ISR(155);
    SET_KERNEL_ISR(156);
    SET_KERNEL_ISR(157);
    SET_KERNEL_ISR(158);
    SET_KERNEL_ISR(159);
    SET_KERNEL_ISR(160);
    SET_KERNEL_ISR(161);
    SET_KERNEL_ISR(162);
    SET_KERNEL_ISR(163);
    SET_KERNEL_ISR(164);
    SET_KERNEL_ISR(165);
    SET_KERNEL_ISR(166);
    SET_KERNEL_ISR(167);
    SET_KERNEL_ISR(168);
    SET_KERNEL_ISR(169);
    SET_KERNEL_ISR(170);
    SET_KERNEL_ISR(171);
    SET_KERNEL_ISR(172);
    SET_KERNEL_ISR(173);
    SET_KERNEL_ISR(174);
    SET_KERNEL_ISR(175);
    SET_KERNEL_ISR(176);
    SET_KERNEL_ISR(177);
    SET_KERNEL_ISR(178);
    SET_KERNEL_ISR(179);
    SET_KERNEL_ISR(180);
    SET_KERNEL_ISR(181);
    SET_KERNEL_ISR(182);
    SET_KERNEL_ISR(183);
    SET_KERNEL_ISR(184);
    SET_KERNEL_ISR(185);
    SET_KERNEL_ISR(186);
    SET_KERNEL_ISR(187);
    SET_KERNEL_ISR(188);
    SET_KERNEL_ISR(189);
    SET_KERNEL_ISR(190);
    SET_KERNEL_ISR(191);
    SET_KERNEL_ISR(192);
    SET_KERNEL_ISR(193);
    SET_KERNEL_ISR(194);
    SET_KERNEL_ISR(195);
    SET_KERNEL_ISR(196);
    SET_KERNEL_ISR(197);
    SET_KERNEL_ISR(198);
    SET_KERNEL_ISR(199);
    SET_KERNEL_ISR(200);
    SET_KERNEL_ISR(201);
    SET_KERNEL_ISR(202);
    SET_KERNEL_ISR(203);
    SET_KERNEL_ISR(204);
    SET_KERNEL_ISR(205);
    SET_KERNEL_ISR(206);
    SET_KERNEL_ISR(207);
    SET_KERNEL_ISR(208);
    SET_KERNEL_ISR(209);
    SET_KERNEL_ISR(210);
    SET_KERNEL_ISR(211);
    SET_KERNEL_ISR(212);
    SET_KERNEL_ISR(213);
    SET_KERNEL_ISR(214);
    SET_KERNEL_ISR(215);
    SET_KERNEL_ISR(216);
    SET_KERNEL_ISR(217);
    SET_KERNEL_ISR(218);
    SET_KERNEL_ISR(219);
    SET_KERNEL_ISR(220);
    SET_KERNEL_ISR(221);
    SET_KERNEL_ISR(222);
    SET_KERNEL_ISR(223);
    SET_KERNEL_ISR(224);
    SET_KERNEL_ISR(225);
    SET_KERNEL_ISR(226);
    SET_KERNEL_ISR(227);
    SET_KERNEL_ISR(228);
    SET_KERNEL_ISR(229);
    SET_KERNEL_ISR(230);
    SET_KERNEL_ISR(231);
    SET_KERNEL_ISR(232);
    SET_KERNEL_ISR(233);
    SET_KERNEL_ISR(234);
    SET_KERNEL_ISR(235);
    SET_KERNEL_ISR(236);
    SET_KERNEL_ISR(237);
    SET_KERNEL_ISR(238);
    SET_KERNEL_ISR(239);
    SET_KERNEL_ISR(240);
    SET_KERNEL_ISR(241);
    SET_KERNEL_ISR(242);
    SET_KERNEL_ISR(243);
    SET_KERNEL_ISR(244);
    SET_KERNEL_ISR(245);
    SET_KERNEL_ISR(246);
    SET_KERNEL_ISR(247);
    SET_KERNEL_ISR(248);
    SET_KERNEL_ISR(249);
    SET_KERNEL_ISR(250);
    SET_KERNEL_ISR(251);
    SET_KERNEL_ISR(252);
    SET_KERNEL_ISR(253);
    SET_KERNEL_ISR(254);
    SET_KERNEL_ISR(255);

    __asm__ volatile("lidt %0" : : "m"(idt));
}