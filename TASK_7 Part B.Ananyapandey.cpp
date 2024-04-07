#include <iostream>
#include <vector>
#include <queue>
#include <opencv2/opencv.hpp>

class GridSolver {
private:
    cv::Mat image;
    int rows, cols;

public:
    GridSolver(const std::string& filename) {
        image = cv::imread(filename, cv::IMREAD_COLOR);
        if (image.empty()) {
            std::cerr << "Error: Unable to read image file." << std::endl;
            return;
        }
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
        rows = image.rows;
        cols = image.cols;
    }

    void findShortestPath() {
        std::vector<std::vector<int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        std::queue<std::pair<int, int>> q;
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

        q.push({0, 0});
        visited[0][0] = true;

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            if (x == rows - 1 && y == cols - 1) break;

            for (const auto& dir : dirs) {
                int nx = x + dir[0];
                int ny = y + dir[1];
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny]) {
                    if (image.at<cv::Vec3b>(nx, ny) != cv::Vec3b(0, 0, 255)) {
                        q.push({nx, ny});
                        visited[nx][ny] = true;
                    }
                }
            }
        }

        drawShortestPath(visited);
    }

    void drawShortestPath(const std::vector<std::vector<bool>>& visited) {
        cv::Mat result = image.clone();

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (visited[i][j]) {
                    cv::putText(result, "(" + std::to_string(i + 1) + "," + std::to_string(j + 1) + ")",
                                cv::Point(j * 50, i * 50 + 25), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
                }
            }
        }

        cv::imshow("Shortest Path", result);
        cv::waitKey(0);
    }
};

int main() {
    GridSolver solver("grid_image.png");
    solver.findShortestPath();

    return 0;
}
