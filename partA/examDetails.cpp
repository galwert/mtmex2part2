#include "examDetails.h"
#include <ostream>
#include <utility>

const int MIN_MONTH = 1;
const int MAX_MONTH = 12;
const int MIN_DAY = 1;
const int MAX_DAY = 30;
const int MIN_HOUR = 0;
const int MAX_HOUR = 23;
const int TEN = 10;
const int HALF = 5;
const int THIRTY = 30;

const int FULL_HOUR = 60;
const std::string COURSE_NUMBER_TEXT = "Course Number: ";
const std::string TIME_TEXT = "Time: ";
const std::string AT_TEXT = " at ";
const std::string COLON =  ":";
const std::string ZERO_MINUTES = ":00";
const std::string DURATION_TEXT = "Duration: ";
const std::string ZOOM_LINK_TEXT = "Zoom Link: ";

const std::string DEFAULT_ZOOM_LINK = "https://tinyurl.com/59hzps6m";
const int DEFAULT_COURSE_NUMBER = 234124;
const int DEFAULT_MONTH = 7;
const int DEFAULT_DAY = 28;
const int DEFAULT_HOUR = 13;
const int DEFAULT_LENGTH = 3;

namespace mtm
{
    using std::cout;
    using std::string;
    using std::endl;

    ExamDetails::ExamDetails(int course_number, int test_month, int test_day,
                             double test_hour,int length, std::string&& link)
    {
        if(test_month < MIN_MONTH || test_month > MAX_MONTH || test_day < MIN_DAY || test_day > MAX_DAY)
        {
            throw ExamDetails::InvalidDateException();
        }

        if((int)test_hour < MIN_HOUR || (int)test_hour > MAX_HOUR || length <= 0)
        {
            throw ExamDetails::InvalidTimeException();
        }
        int hour_with_minutes = (int)(test_hour*TEN);
        if(hour_with_minutes % TEN != 0 && hour_with_minutes % TEN != HALF)
        {
            throw ExamDetails::InvalidTimeException();
        }

        this->length=length;
        this->course_number=course_number;
        this->test_day=test_day;
        this->test_month=test_month;
        this->test_hour=test_hour;
        this->link=link;
    }

    ExamDetails::ExamDetails(const ExamDetails& exam_details)
    {
        this->length=exam_details.length;
        this->course_number=exam_details.course_number;
        this->test_day=exam_details.test_day;
        this->test_month=exam_details.test_month;
        this->test_hour=exam_details.test_hour;
        this->link=exam_details.link;
    }

    std::string ExamDetails::getLink() const
    {
        return this->link;
    }
    void ExamDetails::setLink(std::string link1)
    {
        this->link = link1;
    }
    int ExamDetails::operator-(const ExamDetails& exam_details) const
    {
        return (this->test_month-exam_details.test_month)*THIRTY+this->test_day-exam_details.test_day;
    }
    bool ExamDetails::operator<(const ExamDetails& exam_details) const
    {
        if(this->test_month==exam_details.test_month)
        {
            return this->test_day<exam_details.test_day;
        }
        return this->test_month<exam_details.test_month;

    }
    std::ostream& operator<<(std::ostream& os, const ExamDetails& exam_details)
    {
        bool time_zero = false;
        if(FULL_HOUR*(exam_details.test_hour-(int)exam_details.test_hour) == 0)
        {
            time_zero = true;
        }
        os << COURSE_NUMBER_TEXT <<exam_details.course_number<<endl;
        os << TIME_TEXT <<exam_details.test_day<<"."<<exam_details.test_month;
        if(!time_zero)
        {
            os << AT_TEXT << (int) exam_details.test_hour << COLON
               << FULL_HOUR * (exam_details.test_hour - (int) exam_details.test_hour) << endl;
        }
        else
        {
            os << AT_TEXT << (int) exam_details.test_hour << ZERO_MINUTES << endl;
        }
        os<<DURATION_TEXT<<exam_details.length<<ZERO_MINUTES<<endl;
        os<<ZOOM_LINK_TEXT<<exam_details.link<<endl;

        return os;
    }

    ExamDetails ExamDetails::makeMatamExam()
    {
        return ExamDetails(DEFAULT_COURSE_NUMBER, DEFAULT_MONTH, DEFAULT_DAY, (double)DEFAULT_HOUR, DEFAULT_LENGTH,
                           (std::string &&) DEFAULT_ZOOM_LINK);
    }
}
