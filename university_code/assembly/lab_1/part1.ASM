segst	segment para stack  'stack'
	db	64 dup('stack   ')
segst	ends
dseg segment 'data'
   p1 DB -4Ch, 180, -76
   p2 DB 17-2
   p3 DT 187654876
   p4 DT 'rock'
   p5 DW 210
   p6 DW -115
dseg ends
end