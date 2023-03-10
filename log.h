
/***--------------------------------------------------------------------------*/
/*!
 *  @struct     log_lvl_t
 *  @brief      日志等级
 *  @author     Jaly
 *  @date       2017/12/10
 */
#undef LOG
#if JALY_LOG_ENABLE
#undef RAW
#undef ASSERT
#undef ERROR
#undef WARN
#undef INFO
#undef DEBUG
#undef VERBOSE

typedef enum {
    RAW = 0, /*!< always output, raw format */
    ASSERT,     /*!< carash error */
    ERROR,      /*!< error but maybe just show a message */
    WARN,       /*!< warning, may casuse error */
    INFO,       /*!< just show info, like function run */
    DEBUG,      /*!< just for debug */
    VERBOSE,    /*!< after debug, some debug info may not deleted, just set them to verbose */
} log_lvl_t;  /* end of enum define */

/* simple log for user */
extern u32 log_lvl;
extern u32 log_filter;
extern const char* log_color[7];

#define LOG_CTRL_PARAM_DEFINE              \
    u32 log_filter = LOG_FLT_DEFAULT;      \
    log_lvl_t log_lvl = DEBUG;             \
    const char* log_color[7] = {           \
        "\033[0m", /* RAW = no color */    \
        "\033[95m", /* ASSERT = Magenta */ \
        "\033[91m", /* ERROR = red */      \
        "\033[93m", /* WARN = yellow */    \
        "\033[94m", /* INFO = blue	   */   \
        "\033[92m", /* DEBUG = green */    \
        "\033[37m", /* VERBOSE write  */   \
    };

#define LOG_SET_LVL(lvl) log_lvl = lvl
#define LOG_GET_LVL(lvl) lvl = log_lvl

/* redefine LOG_MODULE value for each module, zero is reseverd
 * 0xFFFFFFFF means allow all log output.
 * define each module value as a special table in portal.
 */
#define LOG_FLT_DEFAULT 0xFFFFFFFF

#undef LOG_MODULE
#define LOG_MODULE              LOG_FLT_DEFAULT

/**!
 * log can be output if match filter.
 */
#define LOG_SET_FLT(flt)        log_filter = flt
#define LOG_GET_FLT(flt)        flt = log_filter

#define LOG_FLT_MATCH(flt)      ((log_filter == LOG_FLT_DEFAULT) || (log_filter == flt))
#define LOG_LVL_CHECK(lvl)      (lvl <= log_lvl)

#define LOG(lvl, ...)           LOG##_##lvl(lvl, __VA_ARGS__);
#define LOG_ASSERT(lvl, ...)    LOGx(lvl,__VA_ARGS__);
#define LOG_ERROR(lvl, ...)     LOGx(lvl,__VA_ARGS__);
#define LOG_WARN(lvl, ...)      LOGx(lvl,__VA_ARGS__);
#define LOG_INFO(lvl, ...)      LOGx(lvl,__VA_ARGS__);
#define LOG_DEBUG(lvl, ...)     LOGx(lvl,__VA_ARGS__);
#define LOG_VERBOSE(lvl, ...)   LOGx(lvl, __VA_ARGS__);
#define LOG_RAW(lvl, ...)            \
    if (LOG_FLT_MATCH(LOG_MODULE)) { \
        printf(__VA_ARGS__);         \
    };

#define LOGx(lvl, ...)                                         \
    {                                                          \
        if (LOG_LVL_CHECK(lvl) && LOG_FLT_MATCH(LOG_MODULE)) { \
            printf("%s[%c]\033[0m ", log_color[lvl], #lvl[0]); \
            if (lvl <= WARN) {                                 \
                printf("[%s:%d] ", __FUNCTION__, __LINE__);    \
            }                                                  \
            printf(__VA_ARGS__);                               \
        }                                                      \
    }
#else
#define LOG(lvl, ...) printf(__VA_ARGS__);
#endif
