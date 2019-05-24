/***
 * MIT License
 *
 * Copyright (c) 2016 Luca Weihs
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <vector>
#include "RangeTree.h"
#include <random>
#include <cmath>

namespace RT = RangeTree;

template <typename T>
std::vector<T> abs(std::vector<T> vec) {
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = std::abs(vec[i]);
    }
    return vec;
}

template <typename T>
std::vector<T> add(const std::vector<T>& v0, const std::vector<T>& v1) {
    std::vector<T> v;
    for (int i = 0; i < v0.size(); i++) {
        v.push_back(v0[i] + v1[i]);
    }
    return v;
}

template <typename T, class S>
std::vector<RT::Point<T,S>> slice(std::vector<RT::Point<T,S>> points, int start, int end) {
    std::vector<RT::Point<T,S>> newVec(points.begin() + start, points.begin() + end + 1);
    return newVec;
}

template <typename T, class S>
std::vector<RT::Point<T,S>> sortPoints(std::vector<RT::Point<T,S>> points) {
    RT::PointOrdering<T,S> pointOrdering(0);
    std::sort(points.begin(), points.end(), pointOrdering);
    return points;
}

template <typename T, class S>
std::vector<RT::Point<T,S>> sortAndMerge(std::vector<RT::Point<T,S>> points) {
    if (points.size() == 0) {
        return points;
    }
    RT::PointOrdering<T,S> pointOrdering(0);
    points = sortPoints(points);
    std::vector<RT::Point<T,S>> sortedPoints = {points[0]};
    int k = 0;
    for (int i = 1; i < points.size(); i++) {
        if (pointOrdering.equals(sortedPoints[k], points[i])) {
            sortedPoints[k].increaseCountBy(points[i].count());
        } else {
            sortedPoints.push_back(points[i]);
            k++;
        }
    }
    return sortedPoints;
}

template <typename T, class S>
void printPoints(std::vector<RT::Point<T,S>> points) {
    for (int i = 0; i < points.size(); i++) {
        points[i].print();
    }
}



int main()
{

/*
  //std::vector<double> values = {1.0,1.0,2.0,2.0,3.0,3.0,3.0,4.0,4.0,5.0};
  std::vector<double> values = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0};

  std::vector<RT::Point<double,int>> points = {};

  auto f = [](double a) { std::vector<double> b = {a}; return b;};
  for (int i = 0; i < values.size(); i++) {
      RT::Point<double,int> a(f(values[i]), 0);
      points.push_back(a);
  }

  RT::RangeTree<double,int> rtree(points);

  auto g = [](bool a) { std::vector<bool> b = {a}; return b;};
  int count = rtree.countInRange(f(2.0), f(8.0), g(true), g(true));
  if (count == 7)
    printf("Expected result ok!\n");
  else
    printf("Expected result IS NOT ok!: cout: %d\n", count);

  if (rtree.countInRange(f(2.0), f(4.0), g(true), g(true)) != 3) {
    printf("ITS not ok!\n");

  }

  rtree.print();



*/









    std::vector<int> v1 = {1,2,3,4};
    std::vector<int> v2 = {1,2,3,4};
    std::vector<RT::Point<int,int>> points = {};

    auto f = [](int a, int b) { std::vector<int> c = {a, b}; return c;};
    
    for (int i = 0; i < v1.size(); i++) {
      for (int j = 0; j < v2.size(); j++) {
        RT::Point<int,int> a(f(v1[i], v2[j]), 0);
        points.push_back(a);
      }
    }

    RT::RangeTree<int,int> rtree(points);

    rtree.print();




/*
  RT::Point<double,int> pointout(f(values[9]), 0);
  RT::Point<double,int> pointin(f(10.0), 0);

  rtree.replace(pointin, pointout);



  if (rtree.countInRange(f(9.0), f(11.0), g(true), g(true)) == 1) {
    printf("Oh yaaa!\n");

  }


  auto f = [](double a, double b, double c) { std::vector<double> d = {a, b, c}; return d;};
  std::vector<RT::Point<double,int>> points = {};
  for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
          for (int k = 0; k < 3; k++) {
              RT::Point<double,int> a(f(i, j, k), 0);
              points.push_back(a);
              if (i == 1 && j == 1 && k == 1) {
                  points.push_back(a);
              }
          }
      }
  }
  RT::RangeTree<double,int> rtree(points);
  RT::Point<double,int> a(f(0, 0, 0), 0);
  RT::Point<double,int> b(f(8, 8, 8), 0);

  rtree.replace(a, b);

  rtree.countInRange(f(2.0), f(4.0), g(false), g(true)), 5);
  rtree.countInRange(f(2.0), f(4.0), g(true), g(false)), 5);
  rtree.countInRange(f(2.0), f(4.0), g(false), g(false)), 3);
  rtree.countInRange(f(3.0), f(3.0), g(false), g(false)), 0);
  rtree.countInRange(f(3.0), f(4.0), g(false), g(false)), 0);*/

}
