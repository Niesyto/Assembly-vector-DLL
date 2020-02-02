.data

.code

calc PROC	

		;Zgodnie z calling convention:
		;rcx - adres pierwszego argumentu (sumy)
		;rdx - adres drugiego argumentu (fragment wektora widths)
		;r8 - adres trzeciego argumentu (fragment wektora heights)
		;r9 - ilo�� danych


		;Zapis 4 element�w widths do xmm0, tu rozpoczyna si� g��wna p�tla programu
L1:		movaps	xmm0,  [rdx]
		;Zapis 4 element�w heights do xmm1
		movaps	xmm1,  [r8]
		;Pomno�enie kolejnych element�w xmm1 i xmm0 przez siebie
		mulps	xmm0,xmm1

		;Dodanie sumy mno�enia do xmm2
		addps xmm2,xmm0
	
		;Inkrementacja wska�nik�w tablic
		add rdx,16;
		add r8,16;

		;Dekrementacja licznika p�tli
		sub r9,4
		;Skok je�eli p�tla sie nie sko�czy�a
		jne L1


		;Horizontal sum 
		haddps	xmm2,xmm2
		;Kolejne Horizontal sum 
		haddps	xmm2,xmm2
		;Po dw�ch operacjach haddps w xmm2 s� cztery sumy iloczyn�w widths i heights

		;Zapis nowej sumy w *sum
		movss	DWORD PTR[rcx],xmm2

		;Powr�t
		ret

calc endp						

end