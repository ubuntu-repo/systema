
dec printf: func (fmt: @[byte], ...) returns byte;
dec fact  : func (num:   byte);

def abc as four := 5;

sub fact(num: four) returns four
    def f as four;
    def i as four;
begin
    for i from 10 down to 1 step -2 do
        printf("%d\n", i);
    loop;
    return f;
end;

sub main(argc: four, argv: @[@[byte]]) returns byte
    def i  as four;
    def y  as eigh := 1;
    def ax as twin in register("%di") := 3;
begin
    i := 0;
    while i < argc do
        printf("arg %d: %s\n", i, argv@[i]);
        i++;
    loop;
    return 0;
end;