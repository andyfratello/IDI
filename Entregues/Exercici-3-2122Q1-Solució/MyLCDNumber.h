
#include <QLCDNumber>

class MyLCDNumber: public QLCDNumber {
	Q_OBJECT

	public:
		MyLCDNumber(QWidget *parent);
        int total;

	public slots:
	    void suma();
        void reinicia();
};
