# Union Booth

This project is a combination of Live Questions, FAQ and Support Resources repository functionality meant to be a helper tool for educators doing Online Delivery.

Planned functionality is having unique cohort spaces, timed unlock for lessons, live questions supported by sockets, admin space to monitor and moderate the questions, persistent FAQ and Additional Lesson Resources.

## Project Structure

- `/register` - Register a new student or educator
- `/login` - Logs in a student or educator
- `/` - Current lecture + history of lectures (grouped by Unit, weekly?)
- `/live` - Live questions for current lecture (ask a question, thumb up other questions, order by thumbs)
- `/lecture/:lectureId` - Previous answered live questions, curated FAQ and Additional Resources
- `/resources/:lectureId` - Resources only view
- `/profile` - Manage user account (change password)
- `/admin/users` - User management (invite user, approve user, manage user priviliges)
- `/admin/live` - Management of current live questions (tagging questions as "answering" or "answered", answer field using Markdown)