Monkey 0:
  Starting items: 57
  Operation: new = old * 13
  Test: divisible by 11
    If true: throw to monkey 3
    If false: throw to monkey 2

Monkey 1:
  Starting items: 58, 93, 88, 81, 72, 73, 65
  Operation: new = old + 2
  Test: divisible by 7
    If true: throw to monkey 6
    If false: throw to monkey 7

Monkey 2:
  Starting items: 65, 95
  Operation: new = old + 6
  Test: divisible by 13
    If true: throw to monkey 3
    If false: throw to monkey 5

Monkey 3:
  Starting items: 58, 80, 81, 83
  Operation: new = old * old
  Test: divisible by 5
    If true: throw to monkey 4
    If false: throw to monkey 5

Monkey 4:
  Starting items: 58, 89, 90, 96, 55
  Operation: new = old + 3
  Test: divisible by 3
    If true: throw to monkey 1
    If false: throw to monkey 7

Monkey 5:
  Starting items: 66, 73, 87, 58, 62, 67
  Operation: new = old * 7
  Test: divisible by 17
    If true: throw to monkey 4
    If false: throw to monkey 1

Monkey 6:
  Starting items: 85, 55, 89
  Operation: new = old + 4
  Test: divisible by 2
    If true: throw to monkey 2
    If false: throw to monkey 0

Monkey 7:
  Starting items: 73, 80, 54, 94, 90, 52, 69, 58
  Operation: new = old + 7
  Test: divisible by 19
    If true: throw to monkey 6
    If false: throw to monkey 0
