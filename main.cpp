#include <QCoreApplication>
#include <KCompressionDevice>
int main(int argc, char**argv) {
     QCoreApplication qapp(argc, argv);
    KCompressionDevice dev("test.gz", KCompressionDevice::GZip);
    dev.open(QIODevice::WriteOnly);
    dev.write("Hello world!\n");
    dev.close();
    return 0;
}
