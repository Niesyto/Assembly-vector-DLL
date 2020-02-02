.data

.code

calc PROC	

		;Zgodnie z calling convention:
		;rcx - adres pierwszego argumentu (sumy)
		;rdx - adres drugiego argumentu (fragment wektora widths)
		;r8 - adres trzeciego argumentu (fragment wektora heights)
		;r9 - iloœæ danych


		;Zapis 4 elementów widths do xmm0, tu rozpoczyna siê g³ówna pêtla programu
L1:		movaps	xmm0,  [rdx]
		;Zapis 4 elementów heights do xmm1
		movaps	xmm1,  [r8]
		;Pomno¿enie kolejnych elementów xmm1 i xmm0 przez siebie
		mulps	xmm0,xmm1

		;Dodanie sumy mno¿enia do xmm2
		addps xmm2,xmm0
	
		;Inkrementacja wskaŸników tablic
		add rdx,16;
		add r8,16;

		;Dekrementacja licznika pêtli
		sub r9,4
		;Skok je¿eli pêtla sie nie skoñczy³a
		jne L1


		;Horizontal sum 
		haddps	xmm2,xmm2
		;Kolejne Horizontal sum 
		haddps	xmm2,xmm2
		;Po dwóch operacjach haddps w xmm2 s¹ cztery sumy iloczynów widths i heights

		;Zapis nowej sumy w *sum
		movss	DWORD PTR[rcx],xmm2

		;Powrót
		ret

calc endp						

end