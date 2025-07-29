using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics.Eventing.Reader;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ToDoService.V1;

namespace To_doClient
{
    public class BindableToDo(ToDo grpcTodo) : INotifyPropertyChanged
    {
        private readonly ToDo Todo = grpcTodo;

        public delegate void StatusChangedEventHandler(object sender, Status newStatus);
        public event StatusChangedEventHandler StatusChanged;
        protected void OnStatusChanged(Status newStatus) => StatusChanged?.Invoke(this, newStatus);

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string name) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));

        public string Id => Todo.Id;

        public string Description
        {
            get => Todo.Description;
            set
            {
                Todo.Description = value;
                OnPropertyChanged(nameof(Description));
            }
        }
        public Status GetStatus()
        {
            return Todo.Status;
        }
        /*public void SetStatus(Status value)
        {
            Todo.Status = value;
            OnStatusChanged(value);
            OnPropertyChanged(nameof(Status));
        }
        */
        public void SetStatusNoUpdate (Status value)
        {
            Todo.Status = value;
            OnPropertyChanged(nameof(Status));
        }
        public void SetStatusUpdate(Status value)
        {
            Todo.Status = value;
            OnStatusChanged(value);
            OnPropertyChanged(nameof(Status));
        }
        /*public Status Status
        {
            get => Todo.Status;
        }*/

        public bool Status
        {
            get => Todo.Status == ToDoService.V1.Status.Completed;
            set
            {
                if (value == true)
                {
                    Todo.Status = ToDoService.V1.Status.Completed;
                }
                else
                {
                    Todo.Status = ToDoService.V1.Status.Pending;
                }
                OnStatusChanged(Todo.Status);
                OnPropertyChanged(nameof(Status));
            }
        }

        public ToDo GetOriginal() => Todo;
    }
}
