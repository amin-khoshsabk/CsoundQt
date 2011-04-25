<CsoundSynthesizer>

; Id: H07_REV01.CSD mg (2006, rev.2009)
; author: marco gasperini (marcogsp at yahoo dot it)

; G.M. Koenig
; ESSAY (1957)

<CsOptions>
-W -f -oH07_REV01.wav
</CsOptions>

<CsInstruments>

sr     = 192000
kr     = 192000
ksmps  = 1
nchnls = 1

;=============================================
; 284.1 REVERBERATION
;=============================================
	instr 1
iampr	= ampdb(p4)
ifile	= p5

a1	diskin2 ifile , 1

ar	nreverb a1, 5, .3

; decreasing and increasing reverberation
aenvr	expseg  1, 2.2, ampdb(-30) , 2.2, 1 , p3-4.4, 1
aenv	expseg .1, 2.2, 1, 2.2, .25,  p3-4.4, 0.0001

aout	=  (a1*aenv) +(ar*aenvr*iampr) 
aout	atonex aout, 10

	out aout
	endin
;=============================================

</CsInstruments>
<CsScore>
t0	4572		; 76.2 cm/sec. tape speed (durations in cm)

;			p4	p5
;			iampr	ifile
i1	0	723	-12	"H06_TR01.wav"

;durrev= 5*76.2 = 381
; dur = 342 + durrev
e

</CsScore>
</CsoundSynthesizer>