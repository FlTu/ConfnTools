INCLUDE=-I /usr/include/podofo/ -I /usr/include/boost/
LDD=-lpodofo -lboost_container -lboost_regex
OUT=pdfGen

all:$(OUT)

$(OUT):*.cpp
	g++ *.cpp $(INCLUDE) -o $(OUT) $(LDD)

clean:
	rm $(OUT)
