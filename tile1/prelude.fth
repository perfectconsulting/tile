(:) 0=
0 = (;)

(:) 0<
0 < (;)

(:) 0>
0 > (;)

(:) <>
= not (;)

(:) -
minus + (;)

(:) d-
dminus d+ (;)

(:) 1+
1 + (;)

(:) 1-
1 - (;)

(:) 2+
2 + (;)

(:) 2-
2 - (;)

(:) +!
dup @ rot + swap ! (;)

(:) +C!
dup c@ rot + swap c! (;)

(:) here
0 @ (;)

(:) allot
here + 0 ! (;)

(:) last
12 @ @ (;)

(:) pfa
14 @ 5 + + (;)

(:) cfa
2- (;)

(:) lfa
cfa 2- (;)

(:) nfa
lfa 14 0 1+ - (;)

(:) ,
here ! 2 0 +! (;)

(:) C,
here c! 1 0 +! (;)

(:) immediate
last dup c@ 128 or swap c! (;)

(:) [
0 2 ! (;) immediate

(:) ]
-1 2 ! (;)

(:) -find
32 word here last (find) dup not 0branch [ 22 , ]
drop drop here 12 @ 2- @ @ (find) (;)

(:) '
-find 0branch [ 14 , ] swap drop pfa cfa branch [ 8 , ] drop 0 (;)

(:) 2dup
over over (;)

(:) -dup
dup 0branch [ 4 , ] dup (;)

(:) 2drop
drop drop (;)

(:) 2swap
>r rot rot r> rot rot (;)

(:) 2over
>r >r 2dup r> r> 2swap (;)

(:) literal
[ ' lit , ] [ ' lit , ] , , (;) immediate

(:) ca!
last pfa cfa ! (;)

(:) scode
r> ca! (;)

(:) ;code
[ ' scode ] literal , 0 2 ! (;) immediate

(:) constant
create , ;code 501 ,

(:) <builds
0 constant (;)

(:) does>
r> last pfa cfa 2+ ! ;code 901 ,

(:) variable
<builds 0 , does> (;)

0 constant DP
2 constant STATE
4 constant TIB
6 constant IN
8 constant BASE
10 constant CURRENT
12 constant CONTEXT
14 constant WIDTH
16 constant OUT
18 constant INNER
20 constant HLD
22 constant FENCE
32 constant BL
64 constant C/L
0 constant FALSE
-1 constant TRUE

(:) hex
16 BASE ! (;)

(:) binary
2 BASE ! (;)

(:) decimal
10 BASE ! (;)

(:) s->d
dup 0< (;)

(:) ++
1 swap +! (;)

(:) --
-1 swap +! (;)

(:) +-
0< 0branch [ 4 , ] minus (;)

(:) d+-
0< 0branch [ 4 , ] minus (;)

(:) abs
dup +- (;)

(:) dabs
dup d+- (;)

(:) min
2dup > 0branch [ 4 , ] swap drop (;)

(:) max
2dup < 0branch [ 4 , ] swap drop (;)

(:) m*
2dup xor >r abs swap abs u* r> d+- (;)

(:) m/
over >r >r dabs r abs u/ r> r xor +- swap r> +- swap (;)

(:) *
m* drop (;)

(:) /mod
>r s->d r> m/ (;)

(:) /
/mod swap drop (;)

(:) mod
/mod drop (;)

(:) */mod
>r m* r> m/ (;)

(:) */
*/mod swap drop (;)

(:) m/mod
>r 0 r u/ r> swap >r u/ r> (;)

(:) fill
>r dup 0> [ ' 0branch , 18 , ] 1- 2dup + r swap c!
[ ' branch , -22 , ] r> drop drop drop (;)

(:) move
dup 0> [ ' 0branch , 30 , ] 1- rot rot over @ over !
2+ swap 2+ swap rot [ ' branch , -34 , ] 2drop drop (;)

(:) cmove
dup 0> [ ' 0branch , 30 , ] 1- rot rot over c@ over c!
1+ swap 1+ swap rot [ ' branch , -34 , ] 2drop drop (;)

(:) emit
(emit) 1 OUT +! (;)

(:) cr
13 emit 10 emit 0 OUT ! (;)

(:) space
BL emit (;)

(:) spaces
0 max -dup 0branch [ 14 , ] 0
(do) space (loop) [ -4 , ] (;)

(:) count
dup 1+ swap c@ (;)

(:) type
-dup 0branch [ 18 , ] over + swap
(do) i c@ emit (loop) [ -8 , ]
branch [ 4 , ] drop (;)

(:) hold
HLD -- HLD @ c! (;)

(:) pad
here 68 + (;)

(:) <#
pad HLD ! (;)

(:) #>
drop drop HLD @ pad over - (;)

(:) sign
rot 0< 0branch [ 8 , ] 45 hold (;)

(:) #
BASE @ m/mod rot 9 over < 0branch [ 8 , ] 39 + 48 + hold (;)

(:) #s
# 2dup or 0= 0branch [ -10 , ] (;)

(:) d.r
>r swap over dabs <# #s sign #> r> over - spaces type (;)

(:) .r
>r s->d r> d.r (;)

(:) d.
0 d.r space (;)

(:) u.
0 d. (;)

(:) .
s->d d. (;)

(:) ."
STATE @ 0branch [ 26 , ]
[ ' (.") ] literal , here 34 word c@ 1+ allot branch [ 14 , ]
34 word here count type (;) immediate

(:) ?comp
STATE @ not 0branch [ 54 , ]
." Error - Word may only be used when compiling." cr abort (;)

(:) ?exec
STATE @ 0branch [ 54 , ]
." Error - Word may only be used when executing." cr abort (;)

(:) ?pairs
- 0 <> 0branch [ 35 , ]
." Error - Pairs don't match." cr abort (;)

(:) vocabulary
<builds CONTEXT @ , last , does> 2+ CONTEXT ! (;)

(:) definitions
CONTEXT @ CURRENT ! (;)

(:) seal
here dup 1 C, 0 C, WIDTH @ 1+ + DP ! 0 , CONTEXT @ ! (;)

(:) id.
count 63 and WIDTH @ min type (;)

vocabulary tile
tile definitions

(:) words
." Context vocabulary : " CONTEXT @ WIDTH @ 9 + - id. cr
." Current vocabulary : " CURRENT @ WIDTH @ 9 + - id. cr
C/L 1+ OUT ! last
OUT @ C/L > 0branch [ 4 , ] cr dup id. space space pfa lfa @ dup
0= 0branch [ -34 , ] drop cr (;)

(:) if
?comp [ ' 0branch ] literal , here 0 , 2 (;) immediate

(:) (endif)
?comp 2 ?pairs here over - swap ! (;)

(:) then
(endif) (;) immediate

(:) else
2	?pairs [ ' branch ] literal , here 0 , swap 2 (endif) 2 (;)
immediate

(:) begin
?comp here 1 (;) immediate

(:) again
?comp 1 ?pairs [ ' branch ] literal , here - ,	(;) immediate

(:) until
?comp 1 ?pairs [ ' 0branch ] literal , here - ,	(;) immediate

(:) while
?comp 1 ?pairs [ ' 0branch ] literal , here 0 , 4 (;) immediate

(:) repeat
?comp 4 ?pairs [ ' branch ] literal , swap here - ,
dup here swap - swap !	(;) immediate

(:) do
[ ' (do) ] literal , here 3 (;) immediate

(:) loop
3	?pairs ?comp [ ' (loop) ] literal , here - ,	(;) immediate

(:) +loop
3	?pairs ?comp [ ' (+loop) ] literal , here - ,	(;) immediate

(:) compile
?comp r> dup 2+ >r @ ,	(;)

(:) [compile]
' dup 0= if
." Not in context vocabulary." cr abort
then
, (;) immediate

(:) (toggle)
over over and if not and else or then (;)

(:) toggle
over c@ swap (toggle) swap c! (;)

(:) smudge
last 64 toggle (;)

(:) :
?exec 0 (:) smudge (;) immediate

(:) ;
?comp 0 ?pairs [ ' (;) , ] smudge (;) immediate

(:) R:
?exec 0 (:)	(;) immediate

(:) R;
?comp 0 ?pairs [ ' (;) , ] (;) immediate

(:) unlink
CONTEXT @ 2- @ CONTEXT ! definitions (;)

(:) forget
-find 0=
if
." Not in context vocabulary." cr drop
else
swap drop
dup FENCE @ <
if
." In protected vocabulary." cr drop
else
dup pfa 4 + CONTEXT @ = if
unlink ." Unlinking vocabulary." cr
then
dup DP ! pfa lfa @ CONTEXT @ ! definitions
then
then (;)

(:) bytes
-1 0 here s->d d- <# #s #> type space (;)

(:) free
bytes ." bytes of dictionary remaining." cr (;)
here FENCE !
free
R: s.
empty? not
if
>r s. r> dup .
then R;


