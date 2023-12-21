#include "charts.h"
#include "stdafx.h"
#include "testing.h"
using namespace std;

static void writeTopBoilerPlateOfPieChar(ostream& out) {
    out << "<html>\n";
    out << "<head>\n";
    out << "<script type = \"text/javascript\" src = \"https://www.gstatic.com/charts/loader.js\"></script>\n";
    out << "<script type = \"text/javascript\">\n";
    out << "google.charts.load(\"current\", { packages: [\"corechart\"] });\n";
    out << "google.charts.setOnLoadCallback(drawChart);\n";
    out << "function drawChart() {\n";
    out << "var data = google.visualization.arrayToDataTable([\n";
    out << "['Task', 'Hours per Day'],\n";
}

static void writeFixedPieChartData(ostream& out) {
    out << "['Work', 11],\n";
    out << "['Eat', 2],\n";
    out << "['Commute',  2],\n";
    out << "['Watch TV', 2],\n";
    out << "['Sleep', 7]\n";
}

static void writeBottomBoilerPlateOfPieChar(ostream& out) {
    out << "]);\n";
    out << "var options = {\n";
    out << "title: 'My Daily Activities',\n";
    out << "is3D : true,\n";
    out << "};\n";
    out << "var chart = new google.visualization.PieChart(document.getElementById('piechart_3d'));\n";
    out << "chart.draw(data, options);\n";
    out << "}\n";
    out << "</script>\n";
    out << "</head>\n";
    out << "<body>\n";
    out << "<div id = \"piechart_3d\" style = \"width: 900px; height: 500px;\"></div>\n";
    out << "</body>\n";
    out << "</html>\n";
}

static void generateFixedPieChart() {
    ofstream out;
    out.open("./outputFiles/fixedChart.html");
    writeTopBoilerPlateOfPieChar(out);
    writeFixedPieChartData(out);
    writeBottomBoilerPlateOfPieChar(out);
}

static void writePieChartData(ostream& out, const vector<string>& labels, const vector<double>& values) {
    int nLabels = (int)labels.size();
    for (int i = 0; i < nLabels; i++) {
        string label = labels[i];
        double value = values[i];
        out << "['" << label << "', " << value << "]";
        if (i == nLabels - 1) {
            out << "\n";
        }
        else {
            out << ",\n";
        }
    }
}

static void testWritePieChartData() {
    
    // generate output from the function
    stringstream out;
    vector<string> labels(3);
    vector<double> values(3);
    for (int i = 0; i < 3; i++) {
        stringstream ss;
        ss << "A Label " << i;
        labels[i] = ss.str();
        INFO(labels[i]);
        values[i] = (double)i;
    }
    writePieChartData(out, labels, values);
    string outString = out.str();

    // compare expected and output
    stringstream expected;
    expected << "['A Label 0', 0],\n";
    expected << "['A Label 1', 1],\n";
    expected << "['A Label 2', 2]\n";
    string expectedStr = expected.str();
    ASSERT(outString == expectedStr);
}

void testCharts() {
    TEST(generateFixedPieChart);
    TEST(testWritePieChartData);
}

void pieChart(const string& filename, const vector<string>& labels, const vector<double>& values) {
    
    ofstream out;
    out.open(filename.c_str());
    writeTopBoilerPlateOfPieChar(out);
    writePieChartData(out, labels, values);
    writeBottomBoilerPlateOfPieChar(out);

}