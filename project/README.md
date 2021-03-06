# Union Booth

This project is a combination of Live Questions, FAQ and Support Resources repository functionality meant to be a helper tool for educators doing Online Delivery.

Planned functionality is having unique cohort spaces, timed unlock for lessons, live questions supported by sockets, admin space to monitor and moderate the questions, persistent FAQ and Additional Lesson Resources.

Current functionality is being able to register for an account, support for account roles, adding new topic, managing live discourse, posting questions, replying to the questions and moderating a question as being currently answered.

## Project Structure

- `/register` - Register a new student or educator
- `/login` - Logs in a student or educator
- `/` - Register/Login links for anonymous user, Live questions for current lecture for signed in user (ask a question, add an answer, mark question as being answered by the moderator)
- `/discourse/list` - All Topics in a list
- `/discours/:topicId` - All Questions for a topic
- `/admin` - Admin Section (add new topic, manage existing topics)