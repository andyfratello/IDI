#include <QLabel>

class MyLabel: public QLabel {
	Q_OBJECT

	public:
		MyLabel(QWidget *parent);

	public slots:
	    void cami();
        void esborra();

    signals:
        void nl();
        void nr();
        void clean();
};
