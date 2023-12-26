#include "charts.h"
#include "stdafx.h"
#include "testing.h"
#include "matlib.h"
using namespace std;

static void writeTopBoilerPlateOfLineChart(ostream& out) {
    out << "<html>\n";
    out << "<head>\n";
    out << "<script type = \"text/javascript\" src = \"https://www.gstatic.com/charts/loader.js\"></script>\n";
    out << "<script type = \"text/javascript\">\n";
    out << "google.charts.load('current', {packages: ['corechart', 'line'] });\n";
    out << "google.charts.setOnLoadCallback(drawBackgroundColor);\n";
    out << "function drawBackgroundColor() {\n";
    out << "var data = new google.visualization.DataTable();\n";
}

static void writeBottomBoilerPlateOfLineChart(ostream& out) {
    out << "var options = {\n";
    out << "hAxis: {\n";
    out << "title: 'Time'\n";
    out << "},\n";
    out << "vAxis : {\n";
    out << "title: 'Popularity'\n";
    out << "},\n";
    out << "backgroundColor : '#f1f8e9'\n";
    out << "};\n";

    out << "var chart = new google.visualization.LineChart(document.getElementById('chart_div'));\n";
    out << "chart.draw(data, options);\n";
    out << "}\n";
    out << "</script>\n";
    out << "</head>\n";
    out << "<body>\n";
    out << "<div id = \"chart_div\" style = \"width: 1000px; height: 500px\"></div>\n";
    out << "</body>\n";
}

static void writeFixedLineChartData(ostream& out) {
    out << "data.addColumn('number', 'X')\n";
    out << "data.addColumn('number', 'Cats')\n";

    out << "data.addRows([\n";
    out << "[0, 0], [1, 10], [2, 23], [3, 17], [4, 18], [5, 9], [6, 11], [7, 27], [8, 33], [9, 40], [10, 32], [11, 35], [12, 30], [13, 40], [14, 42], [15, 47], [16, 44], [17, 48], [18, 52], [19, 54], [20, 42], [21, 55], [22, 56], [23, 57], [24, 60], [25, 50], [26, 52], [27, 51], [28, 49], [29, 53], [30, 55], [31, 60], [32, 61], [33, 59], [34, 62], [35, 65], [36, 62], [37, 58], [38, 55], [39, 61], [40, 64], [41, 65], [42, 63], [43, 66], [44, 67], [45, 69], [46, 69], [47, 70], [48, 72], [49, 68], [50, 66], [51, 65], [52, 67], [53, 70], [54, 71], [55, 72], [56, 73], [57, 75], [58, 70], [59, 68], [60, 64], [61, 60], [62, 65], [63, 67], [64, 68], [65, 69], [66, 70], [67, 72], [68, 75], [69, 80]\n";
    out << "])\n";
}

static void generateFixedLineChart() {
    ofstream out;
    out.open("./outputFiles/fixedLineChart.html");
    writeTopBoilerPlateOfLineChart(out);
    writeFixedLineChartData(out);
    writeBottomBoilerPlateOfLineChart(out);
}


// PIE CHART
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
    out.open("./outputFiles/fixedPieChart.html");
    writeTopBoilerPlateOfPieChar(out);
    writeFixedPieChartData(out);
    writeBottomBoilerPlateOfPieChar(out);
}

static void writeLineChartData(ostream& out, const vector<double>& x, const vector<double>& y) {
    int numPoints = (int)x.size();
    ASSERT((int)x.size() == (int)y.size());
    
    // start writing to ostream
    out << "data.addColumn('number', 'X')\n";
    out << "data.addColumn('number', 'f(x) = x*x')\n";
    out << "data.addRows([\n";
    for (int i = 0; i < numPoints; i++) {

        if (i != numPoints - 1) {
            out << "[" << x[i] << ", " << y[i] << "], ";
        }
        else {
            out << "[" << x[i] << ", " << y[i] << "]\n";
        }
    }
    out << "])\n";
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

/////////////////////////
///     Testing     /////
/////////////////////////

static void testWriteLineChartData() {

    // generate output from the function
    vector<double> x(3), y(3);
    for (int i = 0; i < 3; i++) {
        x[i] = i;
        y[i] = i * i;
    }
    stringstream out;
    writeLineChartData(out, x, y);
    string outputString = out.str();
    DEBUG_PRINT("outputString\n" << outputString);

    // generate expected output
    stringstream expected;
    expected << "data.addColumn('number', 'X')\n";
    expected << "data.addColumn('number', 'f(x) = x*x')\n";
    expected << "data.addRows([\n";
    expected << "[0, 0], [1, 1], [2, 4]\n";
    expected << "])\n";
    string expectedStr = expected.str();
    DEBUG_PRINT("expectedStr\n" << expectedStr);

    ASSERT(outputString == expectedStr);

}

static void testWritePieChartData() {
    
    // generate output from the function
    vector<string> labels(3);
    vector<double> values(3);
    for (int i = 0; i < 3; i++) {
        stringstream ss;
        ss << "A Label " << i;
        labels[i] = ss.str();
        INFO(labels[i]);
        values[i] = (double)i;
    }
    stringstream out;
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

void lineChart(const string& filename, const vector<double>& x, const vector<double>& y) {
    ofstream out;
    out.open(filename.c_str());
    writeTopBoilerPlateOfLineChart(out);
    writeLineChartData(out, x, y);
    writeBottomBoilerPlateOfLineChart(out);
}

void pieChart(const string& filename, const vector<string>& labels, const vector<double>& values) {
    
    ofstream out;
    out.open(filename.c_str());
    writeTopBoilerPlateOfPieChar(out);
    writePieChartData(out, labels, values);
    writeBottomBoilerPlateOfPieChar(out);

}


void testCharts() {
    setDebugEnabled(false);
    TEST(generateFixedPieChart);

    setDebugEnabled(false);
    TEST(testWritePieChartData);
    
    setDebugEnabled(false);
    TEST(generateFixedLineChart);
    
    setDebugEnabled(true);
    TEST(testWriteLineChartData);
}