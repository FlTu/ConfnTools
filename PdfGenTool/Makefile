INCLUDE=-I /usr/include/podofo/
LDD=-lpodofo
OUT=pdfGen

all:$(OUT)

$(OUT):*.cpp
	g++ *.cpp $(INCLUDE) -o $(OUT) $(LDD)

clean:
	rm $(OUT)
