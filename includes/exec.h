#ifndef EXEC_H
# define EXEC_H

# include "parsing.h"
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_constants
{
	int						error;
	int						success;
	int						buff_size;
	int						empty;
	int						pipe;
	int						end;
	int						stdin_fd;
	int						stdout_fd;
	int						stderr_fd;
	int						skip;
	int						no_skip;
	int						unknown_command;
	int						is_directory;
	char					**my_env;
}							t_const;

extern t_const				g_n;

typedef struct s_env
{
	char					*value;
	int						exported;
	struct s_env			*next;
}							t_env;

typedef struct s_sig
{
	int						sigint;
	int						sigquit;
	int						exit_status;
	pid_t					pid;
}							t_sig;

typedef struct s_exec_info
{
	int						prev_pipe;
	int						has_next;
	int						*pipefd;
}							t_exec_info;

typedef struct s_mini
{
	t_cmd					*start_cmd;
	t_env					*env;
	t_env					*secret_env;
	int						in;
	int						out;
	int						fdin;
	int						fdout;
	int						pipin;
	int						pipout;
	int						parent;
	int						pid;
	int						ret;
	int						exit;
	int						no_exec;
	int						status;
	int						pipe_read;
}							t_mini;

void						close_and_update_pipe(int *prev_pipe, int *pipefd,
								int has_next);
void						exec_child(t_cmd *cmd, t_mini *mini,
								t_exec_info info);
t_env						*find_var(t_env *env, const char *arg);
int							change_value(t_env *env, const char *arg);
int							is_var_exist(t_env *env, const char *arg);
int							handle_redirs(t_redirections *redir, t_mini *mini);
char						*get_cmd_path(char *cmd, t_env *env);
int							magic_box(char *path, t_cmd *cmd, t_env *env,
								t_mini *mini);
int							env_init(t_mini *mini, char **env_array);
void						free_env(t_env *env);
int							secret_env_init(t_mini *mini, char **env_array);
void						print_sorted_env(t_env *secret);
int							ft_cd(char **args);
char						*env_to_str(t_env *lst);
void						free_tab(char **tab);
void						free_redirections(t_redirections *redir);
void						sort_env(char **tab, int env_len);
void						exec_pipeline(t_mini *mini);
int							env_add(const char *value, t_env *env);
char						*get_env_name(char *dest, const char *src);
int							is_in_env(t_env *env, char *args);
int							is_valid_env(const char *env);
int							ft_export(char **args, t_env *env, t_env *secret);
int							ft_echo(t_mini *mini, char **args);
int							ft_unset(char **a, t_mini *mini);
size_t						env_size(char *env);
int							str_env_len(char **env);
int							ft_pwd(void);
int							ft_env(t_env *env);
size_t						size_env(t_env *lst);
void						ft_exit(t_mini *mini, char **cmd);
int							exec_builtin(char **args, t_mini *mini);
int							is_builtin(char *command);
t_cmd						*get_tokens(char *line);
t_cmd_type					type_arg(char *str);
void						input(t_mini *mini, t_redirections *redir);
void						reset_fds(t_mini *mini);
void						reset_std(t_mini *mini);
void						close_fds(t_mini *mini);
void						free_cmd(t_cmd *start);
void						parse(t_mini *mini);
void						ft_close(int fd);
int							exec_bin(char **args, t_env *env, t_mini *mini);
extern t_sig				g_sig;
#endif