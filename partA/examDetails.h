#ifndef HW2_EXAMDETAILS_H
#define HW2_EXAMDETAILS_H

#include <iostream>
#include "string"
namespace mtm
{
    class ExamDetails
    {
    public:
        int course_number;
        int test_month;
        int test_day;
        double test_hour;
        int length;
        std::string link;

        class InvalidDateException{};
        class InvalidTimeException{};
        class InvalidArgsException {};

        ExamDetails(int course_number, int test_month, int test_day,
                    double test_hour, int length, std::string &&link = std::string());

        ~ExamDetails() = default;

        ExamDetails(const ExamDetails &exam_details);

        ExamDetails &operator=(const ExamDetails &exam_details) = default;

        /**
        * getLink: returns the link to the zoom meeting.
        *
        * @return
        * 	a string with the link to the zoom meeting.
        */
        std::string getLink() const;

        bool operator<(const ExamDetails &exam_details) const;

        /**
        * setLink: sets a new link to the current exam.
        *
        * @param
        * 	link1 - the link to set.
        */
        void setLink(std::string link1);

        int operator-(const ExamDetails &exam_details) const;

        friend std::ostream &operator<<(std::ostream &os, const ExamDetails &exam_details);

        /**
        * makeMatamExam: sets a new matam exam.
        *
        * @return
        * 	a new exam with matam's details.
        */
        static ExamDetails makeMatamExam();
    };
}
#endif //HW2_EXAMDETAILS_H
